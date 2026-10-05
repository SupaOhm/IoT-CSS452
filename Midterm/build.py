#!/usr/bin/env python3
"""Build CHEATSHEET.md and CHEATSHEET.html from cheatsheet.src.md.

    uv run --with markdown python build.py

Each {{sketch:NAME}} line in the source is replaced by the contents of
sketches/NAME/NAME.ino, so a listing in the cheatsheet can never drift from
the sketch you open in the Arduino IDE.
"""
import html
import pathlib
import re
import sys

import markdown

HERE = pathlib.Path(__file__).parent
src = (HERE / "cheatsheet.src.md").read_text()


def include(match):
    name = match.group(1)
    code = (HERE / "sketches" / name / f"{name}.ino").read_text().rstrip("\n")
    return f"Sketch: `sketches/{name}/{name}.ino`\n\n```cpp\n{code}\n```"


body = re.sub(r"^\{\{sketch:(\w+)\}\}$", include, src, flags=re.M)
if "{{sketch:" in body:
    sys.exit("unresolved {{sketch:}} include")


def slug(text):
    text = re.sub(r"[^\w\s-]", "", text).strip().lower()
    return re.sub(r"\s", "-", text)


headings = re.findall(r"^(#{2,3}) (.+)$", re.sub(r"```.*?```", "", body, flags=re.S), flags=re.M)
ids = {slug(t) for _, t in headings}
missing = sorted({a for a in re.findall(r"\]\(#([^)]+)\)", body) if a not in ids})
if missing:
    sys.exit(f"links to headings that do not exist: {missing}")

# --- Markdown: a plain contents list in place of [TOC] ----------------------
contents = "\n".join(f"- [{t}](#{slug(t)})" for h, t in headings if h == "##")
(HERE / "CHEATSHEET.md").write_text(body.replace("[TOC]", contents))

# --- HTML -------------------------------------------------------------------
md = markdown.Markdown(
    extensions=["tables", "fenced_code", "toc", "sane_lists"],
    extension_configs={"toc": {"slugify": lambda value, sep: slug(value), "toc_depth": "2-3"}},
)
page = md.convert(body.replace("[TOC]", ""))
page = page.replace("<li>[ ] ", '<li class="task"><input type="checkbox"> ')
page = re.sub(r"<table>", '<div class="tablewrap"><table>', page)
page = page.replace("</table>", "</table></div>")
title = html.escape(re.search(r"^# (.+)$", body, flags=re.M).group(1))

CSS = """
:root{--bg:#fbfaf7;--panel:#f1efe9;--ink:#1c1b19;--muted:#6a665e;--line:#d9d5cb;
--accent:#0b5c8a;--code:#f4f1ea;--warn:#fff4d6;--warnline:#d9a400}
@media (prefers-color-scheme:dark){:root{--bg:#16181b;--panel:#1e2125;--ink:#e6e3dc;
--muted:#9a968c;--line:#33373d;--accent:#7cc1ea;--code:#1f2327;--warn:#33290a;--warnline:#b08900}}
*{box-sizing:border-box}
html{scroll-padding-top:12px}
body{margin:0;background:var(--bg);color:var(--ink);
font:15px/1.55 -apple-system,BlinkMacSystemFont,"Segoe UI",Helvetica,Arial,sans-serif}
.layout{display:grid;grid-template-columns:290px minmax(0,1fr);min-height:100vh}
nav{position:sticky;top:0;height:100vh;overflow-y:auto;background:var(--panel);
border-right:1px solid var(--line);padding:14px 12px 40px}
nav input{width:100%;padding:8px 10px;border:1px solid var(--line);border-radius:6px;
background:var(--bg);color:var(--ink);font:inherit;margin-bottom:10px}
nav ul{list-style:none;margin:0;padding:0}
nav ul ul{padding-left:12px;margin-bottom:6px}
nav a{display:block;padding:3px 6px;border-radius:4px;color:var(--ink);text-decoration:none;font-size:13.5px}
nav>div>ul>li>a{font-weight:650;margin-top:6px}
nav a:hover{background:var(--line)}
main{padding:28px 40px 120px;max-width:980px}
h1{font-size:28px;line-height:1.2;margin:0 0 12px}
h2{font-size:22px;margin:48px 0 12px;padding-top:14px;border-top:2px solid var(--line)}
h3{font-size:17px;margin:32px 0 8px}
a{color:var(--accent)}
p,li{max-width:78ch}
code{font:13px/1.5 ui-monospace,SFMono-Regular,Menlo,Consolas,monospace;background:var(--code);
padding:1px 4px;border-radius:3px}
pre{position:relative;background:var(--code);border:1px solid var(--line);border-radius:6px;
padding:12px 14px;overflow-x:auto;margin:10px 0 18px}
pre code{background:none;padding:0;white-space:pre}
button.copy{position:absolute;top:6px;right:6px;font:12px/1 inherit;padding:5px 9px;
border:1px solid var(--line);border-radius:5px;background:var(--bg);color:var(--ink);cursor:pointer}
button.copy:hover{border-color:var(--accent);color:var(--accent)}
.tablewrap{overflow-x:auto;margin:10px 0 18px}
table{border-collapse:collapse;font-size:14px}
th,td{border:1px solid var(--line);padding:5px 9px;text-align:left;vertical-align:top}
th{background:var(--panel)}
blockquote{margin:12px 0;padding:8px 14px;background:var(--warn);border-left:4px solid var(--warnline);border-radius:0 6px 6px 0}
blockquote p{margin:4px 0}
li.task{list-style:none;margin-left:-20px}
@media (max-width:860px){.layout{display:block}nav{position:static;height:auto;max-height:40vh}
main{padding:18px 16px 80px}}
@media print{nav,button.copy{display:none}.layout{display:block}main{padding:0;max-width:none}
body{font-size:11px}pre{white-space:pre-wrap;page-break-inside:avoid;border-color:#999}
pre code{white-space:pre-wrap;font-size:9.5px}h2{page-break-before:always}h2:first-of-type{page-break-before:auto}
table{font-size:10px}a{color:inherit;text-decoration:none}}
"""

JS = """
document.querySelectorAll('pre').forEach(function(pre){
  var b=document.createElement('button');b.className='copy';b.textContent='Copy';
  b.addEventListener('click',function(){
    var t=pre.querySelector('code').innerText;
    var done=function(){b.textContent='Copied';setTimeout(function(){b.textContent='Copy'},1200)};
    if(navigator.clipboard&&window.isSecureContext){navigator.clipboard.writeText(t).then(done)}
    else{var a=document.createElement('textarea');a.value=t;document.body.appendChild(a);a.select();
      try{document.execCommand('copy');done()}catch(e){}document.body.removeChild(a)}
  });
  pre.appendChild(b);
});
var q=document.getElementById('q');
q.addEventListener('input',function(){
  var s=q.value.trim().toLowerCase();
  document.querySelectorAll('nav li').forEach(function(li){
    li.hidden=s!==''&&li.textContent.toLowerCase().indexOf(s)===-1;
  });
});
"""

out = f"""<!doctype html>
<html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>{title}</title><style>{CSS}</style></head>
<body><div class="layout">
<nav><input id="q" type="search" placeholder="Filter sections…" aria-label="Filter sections">{md.toc}</nav>
<main>{page}</main>
</div><script>{JS}</script></body></html>
"""
(HERE / "CHEATSHEET.html").write_text(out)
print(f"CHEATSHEET.md   {len((HERE / 'CHEATSHEET.md').read_text().splitlines())} lines")
print(f"CHEATSHEET.html {len(out) // 1024} KB, {page.count('<pre>')} code blocks, {len(ids)} sections")
