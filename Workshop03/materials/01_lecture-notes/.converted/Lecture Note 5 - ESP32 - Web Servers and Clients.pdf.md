Lecture Note 5:
ESP32 – Web Servers
and Clients
CSS452 Internet of Things
Dr. Seksan Laitrakun
School of ICT, SIIT, Thammasat University
1

Outlines
To learn how to use the ESP32's Wi-Fi capabilities to create interactive, web-based IoT
| applications. | We  | will build | the following | projects: |     |     |
| ------------- | --- | ---------- | ------------- | --------- | --- | --- |
• ESP32 as a Web Server: We will create a local web page, hosted on the ESP32, to remotely
control outputs and display live sensor data from your browser.
• ESP32 as a Web Client: We will send data from the ESP32 to a cloud IoT platform, allowing
| you to  | monitor   | your sensors | from anywhere |     | in the | world. |
| ------- | --------- | ------------ | ------------- | --- | ------ | ------ |
| Lecture | Outline:: |              |               |     |        |        |
1. Introduction to a Web Server
2. Basic HTML and CSS
| 3. ESP32 as a Local Web |     |     | Server to Control Actuators |     |     |     |
| ----------------------- | --- | --- | --------------------------- | --- | --- | --- |
4. ESP32 as a Local Web Server to Monitor Sensor Data
5. ESP32 as a Client of Web Services
6. Advanced Topics for ESP32 Web Servers and Clients
2

References
• Random Nerd Tutorials: https://randomnerdtutorials.com/projects-esp32/
• Last Minute Engineers: https://lastminuteengineers.com/esp32-arduino-ide-tutorial/
• Thai Easy Elect (Thai Language): https://blog.thaieasyelec.com/espino32-article-table-
of-contents/
3

1. Introduction to a Web Server
This section consists of
1.1 Client-Server Architectures
1.2 HTTP Transmission Protocol
4

| 1.1 | Client-Server Architectures |     |     |     |     |     |     |
| --- | --------------------------- | --- | --- | --- | --- | --- | --- |
1. Request-response
| This | is the fundamental |     | communication |     | pattern | for the | web. |
| ---- | ------------------ | --- | ------------- | --- | ------- | ------- | ---- |
Client Server
| It's | a simple, | three-step | process: |     |     |     |     |
| ---- | --------- | ---------- | -------- | --- | --- | --- | --- |
1) Request: A client (like your web browser) sends a request message to a server.
|     | • "GET | /homepage.html“ |     |     |     |     |     |
| --- | ------ | --------------- | --- | --- | --- | --- | --- |
2) Process: The server receives the request and processes it.
|     | • Finds | the requested | file. |     |     |     |     |
| --- | ------- | ------------- | ----- | --- | --- | --- | --- |
3) Response: The server sends a response message back to the client.
|     | • Sends | the HTML | code | for the | homepage. |     |     |
| --- | ------- | -------- | ---- | ------- | --------- | --- | --- |
5

| 1.1 | Client-Server Architectures |     |     |     |     |     |     |     |
| --- | --------------------------- | --- | --- | --- | --- | --- | --- | --- |
Ex: How Your Browser Gets a Web Page
When you type a URL and press the Enter, a simple four-step process happens in the
background:
| 1)  | You | Start: | You | type a | URL | into | your | web browser. |
| --- | --- | ------ | --- | ------ | --- | ---- | ---- | ------------ |
2) The Request: Your browser (the Client) sends an HTTP Request to the web server.
|     | •   | “Please | give | me  | the file | for | this | web page.” |
| --- | --- | ------- | ---- | --- | -------- | --- | ---- | ---------- |
3) The Response: The Server finds the requested files (HTML, CSS, etc.) and sends an
|     | HTTP | Response |         | back  | to  | your browser. |       |     |
| --- | ---- | -------- | ------- | ----- | --- | ------------- | ----- | --- |
|     | •    | “Here    | are the | files | you | asked         | for.” |     |
4) The Result: Your browser receives the files and renders the web page on your screen.
6

| 1.1 | Client-Server Architectures |     |
| --- | --------------------------- | --- |
2. Web Server
| What | is a Web | Server? |
| ---- | -------- | ------- |
a) A program that continuously listens for incoming HTTP requests from clients (like
|     | a web | browser). |
| --- | ----- | --------- |
b) When a request is received, it processes it and sends back an HTTP response (like
|     | an HTML | page). |
| --- | ------- | ------ |
7

| 1.2 HTTP Transmission Protocol |     |     |     |     |     |     |     |
| ------------------------------ | --- | --- | --- | --- | --- | --- | --- |
1. Process
Standard procedures when we open a website (the computer we use to open a website is
called a client; the computer that stores the html source code is called a server):
| 1) The | client | sends | a HTTP | request | message | to the | server. |
| ------ | ------ | ----- | ------ | ------- | ------- | ------ | ------- |
2) The server sends a HTTP response message (including a HTML page) to the client.
8

| 1.2 HTTP Transmission Protocol |     |     |     |     |     |     |     |     |
| ------------------------------ | --- | --- | --- | --- | --- | --- | --- | --- |
2. HTTP Request Message Format
The web server will receive the HTTP request message from the client. Its format is
| shown | below |     |     |     |     |     |     |     |
| ----- | ----- | --- | --- | --- | --- | --- | --- | --- |
METHOD  /path-to-resource  HTTP/version-number
Header-Name-1:  value
Header-Name-2:  value
a blank line
[optional request body]
where
| • METHOD |     | = a | request | method, | e.g., | get or | post. |     |
| -------- | --- | --- | ------- | ------- | ----- | ------ | ----- | --- |
• The method “get” will be the method we use (similar to type a URL).
| • /path-to-resource |      |       | = URL   | path  | after | the host     | website | name. |
| ------------------- | ---- | ----- | ------- | ----- | ----- | ------------ | ------- | ----- |
| • Header-Name-1     |      |       | = Host; | value | = the | host website |         | name  |
| • Read              | more | from: |         |       |       |              |         |       |
http://www.w3schools.com/Tags/ref_httpmethods.asp
9

1.2 HTTP Transmission Protocol
2. HTTP Request Message Format
Example: If you type www.example.com/index.html on your web browser and, then,
press enter. Your computer will work as a client and sends the following HTTP
request message to the server:
GET /index.html HTTP/1.1
Host: www.example.com
The HTTP request message itself that is sent out will be one line of texts (to
represent the above HTTP request message):
GET /index.html HTTP/1.1\r\nHost: www.example.com\r\n\r\n
Note: \r = carriage return; \n = go to the new line.
10

| 1.2 | HTTP Transmission Protocol |     |     |     |     |
| --- | -------------------------- | --- | --- | --- | --- |
3. HTTP Response Message
The server will send the HTTP response message to the client. The client’s web browser
will read this message and display the corresponding web page. The format of the HTTP
| response | message |     | is shown | below. |     |
| -------- | ------- | --- | -------- | ------ | --- |
HTTP/version-number     status-code      message
Header-Name-1:   value
Header-Name-2:   value
A blank line
[HTML Body]
| Examples |      | of status-code |     | and message | are: |
| -------- | ---- | -------------- | --- | ----------- | ---- |
| • 200    | OK   |                |     |             |      |
| • 400    | Bad  | Request        |     |             |      |
| • 404    | Not  | Found          |     |             |      |
| Read     | more | from:          |     |             |      |
https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol
11

| 1.2 | HTTP Transmission Protocol |     |     |     |     |     |     |     |     |     |
| --- | -------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
3. HTTP Response Message
| Example: |     | If you |     | type |     |     |     |     |     | HTTP/1.1 200 OK |
| -------- | --- | ------ | --- | ---- | --- | --- | --- | --- | --- | --------------- |
Date: Mon, 23 May 2005 22:38:34 GMT
www.example.com/index.html
Content-Type: text/html; charset=UTF-8
| on your |     | web | browser |     |     | and, | then, |     | press |     |
| ------- | --- | --- | ------- | --- | --- | ---- | ----- | --- | ----- | --- |
Content-Encoding: UTF-8
| enter. | An  | example |     |     | of the | HTTP |     | response |     | Content-Length: 138 |
| ------ | --- | ------- | --- | --- | ------ | ---- | --- | -------- | --- | ------------------- |
Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT
| message |     | (sent | back |     | from | the | web |     | server) |     |
| ------- | --- | ----- | ---- | --- | ---- | --- | --- | --- | ------- | --- |
Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)
| is shown |     | here. |     | The |     | web | browser |     | will |     |
| -------- | --- | ----- | --- | --- | --- | --- | ------- | --- | ---- | --- |
ETag: "3f80f-1b6-3e1cb03b"
Accept-Ranges: bytes
| display | the | web |     | page | corresponding |     |     |     | to the |     |
| ------- | --- | --- | --- | ---- | ------------- | --- | --- | --- | ------ | --- |
Connection: close
| HTML | body. |     |     |     |     |     |     |     |     |     |
| ---- | ----- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
<html>
<head>
<title>An Example Page</title>
</head>
<body>
Hello World, this is a very simple HTML document.
</body>
</html>
12

2. Basic HTML and CSS
In this section, we will build a basic web page with step-by-step instructions, so
that we can easily change how it looks. This section consists of
2.1 Basic HTML
2.2 Basic CSS
13

2.1 Basic HTML
1. Introducing HTML
| • HTML | stands | for Hyper | Text Markup | Language. |
| ------ | ------ | --------- | ----------- | --------- |
• It is the standard language used to structure the content of a web page.
•
HTML uses tags (e.g., <p>, <h1>) to define different elements like paragraphs and
headings.
• A web browser’s job is to read the HTML file and render the content visually based on
| these | tags. |     |     |     |
| ----- | ----- | --- | --- | --- |
14

|     | 2.1 Basic HTML |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| --- | -------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
1. Introducing HTML
|           |     |       |     | •   | The    | first   |           | line |      | of any |          | HTML   |     | document |     |       | is  |
| --------- | --- | ----- | --- | --- | ------ | ------- | --------- | ---- | ---- | ------ | -------- | ------ | --- | -------- | --- | ----- | --- |
| <!DOCTYPE |     | html> |     |     |        |         |           |      |      |        |          |        |     |          |     |       |     |
|           |     |       |     |     | always |         | <!DOCTYPE |      |      |        |          | html>. |     | This     |     | tells | the |
|           |     |       |     |     | web    | browser |           |      | this |        | document |        |     | is       | an  | HTML  |     |
file.
<html>
|     |     |     |     | •   | The     | structure |     |     | of     | the |     | web | page    |     | should |     | go  |
| --- | --- | --- | --- | --- | ------- | --------- | --- | --- | ------ | --- | --- | --- | ------- | --- | ------ | --- | --- |
|     |     |     |     |     | between |           |     | the | <html> |     | and |     | </html> |     | tags.  |     | The |
<head>
|     |           |                  |     |     | <html> |     | tag   | indicates |         |     | the |     | beginning |     |     | of  | a web |
| --- | --------- | ---------------- | --- | --- | ------ | --- | ----- | --------- | ------- | --- | --- | --- | --------- | --- | --- | --- | ----- |
|     |           |                  |     |     | page   |     | and   | the       | </html> |     |     | tag | indicates |     |     | the | end   |
|     | <title>My | Web Page</title> |     |     |        |     |       |           |         |     |     |     |           |     |     |     |       |
|     |           |                  |     |     | of     | the | page. |           |         |     |     |     |           |     |     |     |       |
</head>
|     |     |     |     | •   | The  | HTML |        |     | document |        |     | is  | divided |         |     | into | two  |
| --- | --- | --- | --- | --- | ---- | ---- | ------ | --- | -------- | ------ | --- | --- | ------- | ------- | --- | ---- | ---- |
|     |     |     |     |     | main |      | parts: | the |          | head   | and |     | the     | body.   | The |      | head |
|     |     |     |     |     | goes |      | within |     | the      | <head> |     |     | and     | </head> |     |      | tags |
<body>
|     |            |        |       |     | and     |     | the | body  |     | within |     |     | the | <body> |     |     | and |
| --- | ---------- | ------ | ----- | --- | ------- | --- | --- | ----- | --- | ------ | --- | --- | --- | ------ | --- | --- | --- |
|     | <h1>Hello, | World! | </h1> |     |         |     |     |       |     |        |     |     |     |        |     |     |     |
|     |            |        |       |     | </body> |     |     | tags. |     |        |     |     |     |        |     |     |     |
<p>This is the content you can see. </p> • The head is where you insert data about the
|     |     |     |     |     | HTML |     | document |     |     | that |     | is  | not | directly |     | visible |     |
| --- | --- | --- | --- | --- | ---- | --- | -------- | --- | --- | ---- | --- | --- | --- | -------- | --- | ------- | --- |
</body>
|         |     |     |     |     | to   | the       | end | user,    |       | but       | adds     |           | functionalities |          |      |     | to     |
| ------- | --- | --- | --- | --- | ---- | --------- | --- | -------- | ----- | --------- | -------- | --------- | --------------- | -------- | ---- | --- | ------ |
|         |     |     |     |     | the  | web       |     | page     |       | like      | the      | title,    |                 | scripts, |      |     | styles |
| </html> |     |     |     |     | and  | more      |     | – this   |       | is called |          | metadata. |                 |          |      |     |        |
|         |     |     |     | •   | The  | body      |     | includes |       |           | the      | content   |                 |          | of   | the | page   |
|         |     |     |     |     | like | headings, |     |          | text, |           | buttons, |           | tables,         |          | etc. |     |        |
15

| 2.1 Basic HTML |     |     |     |     |
| -------------- | --- | --- | --- | --- |
Ex: Create a HTML File
1) Open a Text Editor program (you can use any text editor you like, we use Notepad)
| and     | write the | HTML           | texts | below. |
| ------- | --------- | -------------- | ----- | ------ |
| 2) Save | the file  | as index.html. |       |        |
3) Open your browser and drag the HTML file to a browser tab.
4) You will just see a blank page because you haven’t added anything to the HTML file
yet.
16

2.1 Basic HTML
Ex: Create a Title
The title of your web page is the text that shows in the web browser tab.
• The web page title should go between the <title> and </title> tags, that should go
| between | the | <head> | and </head> | tags. |
| ------- | --- | ------ | ----------- | ----- |
• Add a title to your web page by typing the title between <title> and </title> tags, as
| shown | in the | example | below. |     |
| ----- | ------ | ------- | ------ | --- |
17

2.1 Basic HTML
Ex: Create a Heading
| Headings | are used | to structure | the text | on the | web page. |
| -------- | -------- | ------------ | -------- | ------ | --------- |
• Headings begin with an h followed by a number that indicates the heading strength.
•
For example <h1> and </h1> are the tags for heading 1, <h2> and </h2> for heading 2,
| until | heading 6. |     |     |     |     |
| ----- | ---------- | --- | --- | --- | --- |
• The heading tags should be between the <body> and </body> tags. Add some headings
to your document. You can use the following text has a reference.
18

| 2.1 Basic HTML |     |     |     |     |     |
| -------------- | --- | --- | --- | --- | --- |
Ex: Create a Paragraph
| The paragraphs |     | are used | to place | text. |     |
| -------------- | --- | -------- | -------- | ----- | --- |
• Every paragraph should go between the <p> and </p> tags. Add some paragraphs to
| show | the state | of GPIO | 26 and | GPIO | 27. |
| ---- | --------- | ------- | ------ | ---- | --- |
19

| 2.1 | Basic HTML |     |     |     |     |
| --- | ---------- | --- | --- | --- | --- |
Ex: Create a Button
| How | to create | a button: | Use the | <button> | tag. |
| --- | --------- | --------- | ------- | -------- | ---- |
• The text between <button> and </button> becomes the label on the button’s face.
Example Code:
20

| 2.1 | Basic HTML |     |     |     |     |     |
| --- | ---------- | --- | --- | --- | --- | --- |
Ex: Create a Button
| Here | is an | example. |     |     |     |     |
| ---- | ----- | -------- | --- | --- | --- | --- |
• Note that when we click on the buttons, nothing happens because those buttons do not
| have | any  | hyperlink |            | associated | with   | them.    |
| ---- | ---- | --------- | ---------- | ---------- | ------ | -------- |
| • We | need | to add    | hyperlinks |            | to the | buttons. |
21

| 2.1 | Basic HTML |     |     |     |     |     |
| --- | ---------- | --- | --- | --- | --- | --- |
Ex: Create a Hyperlink
HTML links are called hyperlinks. You can add hyperlinks to text, images, buttons, or any
| other | HTML | element. |     |     |     |     |
| ----- | ---- | -------- | --- | --- | --- | --- |
1) To add a hyperlink you use the <a> and </a> tags, in the following format:
|     | <a href="url">element</a> |     |     |     |     |     |
| --- | ------------------------- | --- | --- | --- | --- | --- |
2) Between the <a> and </a> tags, you should place the HTML element you want to
apply the link to. For example, to apply the link to one of the “OFF” buttons:
|     | <a href="url"><button>OFF</button></a> |     |     |     |     |     |
| --- | -------------------------------------- | --- | --- | --- | --- | --- |
3) The href attribute specifies where the link should go. When you click the GPIO 26
ON button, you want to be redirected to the root page followed by /26/on. To do that,
|     | you should                               | add that | URL | to the | href attribute, | as follows: |
| --- | ---------------------------------------- | -------- | --- | ------ | --------------- | ----------- |
|     | <a href="/26/on"><button>ON</button></a> |          |     |        |                 |             |
4) When you click the GPIO 26 OFF button, you want to redirect to /26/off:
|     | <a href="/26/off"><button>OFF</button></a> |     |     |     |     |     |
| --- | ------------------------------------------ | --- | --- | --- | --- | --- |
22

2.1 Basic HTML
Ex: Create a Hyperlink
You should add the appropriate hyperlink to each of your buttons as follows:
23

2.1 Basic HTML
Ex: Create a Hyperlink
At the moment, you get the error “file was not found” because you do not have any file to
that URL.
• Later, this will be solved on the Arduino IDE, because your ESP32 will send different
HTML text when you click on the buttons.
24

| 2.2 | Basic CSS |     |     |     |     |     |
| --- | --------- | --- | --- | --- | --- | --- |
1. Syntax
CSS stands for Cascading Style Sheets and it is used to describe how the elements in a
web page look. It describes a certain part of the page like a particular tag or a particular
set of tags. The CSS can be added to the HTML file or in a separate file that is referenced
by the HTML file. We are going to add the CSS to the HTML file because it is easier to
| add to | the Arduino | IDE. |     |     |     |     |
| ------ | ----------- | ---- | --- | --- | --- | --- |
1) When added to the HTML file, the CSS should go between the <style> and </style>
| tags, | that should | go in | the head | of the | HTML | file. |
| ----- | ----------- | ----- | -------- | ------ | ---- | ----- |
25

2.2 Basic CSS
1. Syntax
2) CSS uses selectors to style your HTML content. The selector points to the HTML
element you want to style. Selectors have properties, which in turn have values. The
style for a certain selector should go between curly brackets {}. The value is attributed
to a property using a colon (:). Every value should end with a semicolon (;). Each
selector can have, and normally does have, more than one property.
26

| 2.2 Basic CSS |     |     |     |     |     |
| ------------- | --- | --- | --- | --- | --- |
2. Styling the Page
If we want to set to the html style which will be applied to the whole web page i.e., all
web page content goes between the <html> and </html> tags, we can design it by using
the html selector. For example, we define the font-family to Helvetica, the content is
displayed as a block, you set 0px for the margins and align all the page at the center using
| “auto”. | The html | selector | will be | defined | as: |
| ------- | -------- | -------- | ------- | ------- | --- |
27

2.2 Basic CSS
2. Styling the Page
| We add  | the html | selector | within | the |
| ------- | -------- | -------- | ------ | --- |
| <style> | tags.    |          |        |     |
28

| 2.2 | Basic CSS |     |     |     |     |     |     |     |
| --- | --------- | --- | --- | --- | --- | --- | --- | --- |
3. Styling the Button
| Next, | we style | the buttons | that | we  | use. |     |     |     |
| ----- | -------- | ----------- | ---- | --- | ---- | --- | --- | --- |
1) We create a class attribute for a button. The syntax of a class attribute is
<element class="classname">
Here, the element is button. The classname for ON will be named button while the
| classname |     | for OFF | will | be button | and button2 | as shown |     | below. |
| --------- | --- | ------- | ---- | --------- | ----------- | -------- | --- | ------ |
<p><a href="/26/on"><button class="button">ON</button></a></p>
<p><a href="/26/off"><button class="button button2">OFF</button></a></p>
| The | buttons | for GPIO26 |     | will | be designed | the same | way. |     |
| --- | ------- | ---------- | --- | ---- | ----------- | -------- | ---- | --- |
29

2.2 Basic CSS
3. Styling the Button
| There   |     | is nothing |       |
| ------- | --- | ---------- | ----- |
| changed |     | since      | we    |
| did     | not | define     | the   |
| style   | of  | the        | class |
| name    |     | button     | and   |
button2.
30

2.2 Basic CSS
3. Styling the Button
2) To specify the style of the classname button, we add the following text into the
index.html.
| The | background-color |     |     | property, |     | as  | the | name |     | suggests, |     |
| --- | ---------------- | --- | --- | --------- | --- | --- | --- | ---- | --- | --------- | --- |
•
| defines     | the button’s |           | background   |       | color.     |     | The     | colors |        | can | be set |
| ----------- | ------------ | --------- | ------------ | ----- | ---------- | --- | ------- | ------ | ------ | --- | ------ |
| by using    | their        | name      | –            | HTML  | recognizes |     |         | basic  | color  |     | names  |
| – or        | by using     | the       | hexadecimal  |       | or         | RGB | color   |        | code   | –   | search |
| on the      | web          | for       | “hexadecimal |       | color      |     | picker” | to     | search |     | for a  |
| hexadecimal |              | reference |              | for   | a specific |     | color.  |        | Here   |     | we’re  |
| using       | hexadecimal  |           | color        | code. |            |     |         |        |        |     |        |
• We set the border property to none, and the button text to
white.
| • The padding defines a space around the button – |     |     |     |     |     |     |     |     | in this  |     |     |
| ------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | --- | -------- | --- | --- |
case we set 16px by 40px.
We set the text decoration to none, font size of 30px,
•
| margin of 2px, and the cursor to a pointer – |     |     |     |     |     |     |     | this will change  |     |     |     |
| -------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | ----------------- | --- | --- | --- |
the cursor to a pointer when you drag the mouse over the
button.
31

2.2 Basic CSS
3. Styling the Button
3) To specify the style of the classname button2, we add the following text into the
index.html.
|     |     |     | Here,     | we only  | define | the color | (grey) | to the |
| --- | --- | --- | --------- | -------- | ------ | --------- | ------ | ------ |
|     |     |     | classname | button2. |        |           |        |        |
The off button belongs to classname “button” and classname “button2”, so it will have
| properties | from | both. |     |     |     |     |     |     |
| ---------- | ---- | ----- | --- | --- | --- | --- | --- | --- |
We add these two CSS styles for the button elements within the <style> tags in the
| index.html | and refresh | the webpage. |     |     |     |     |     |     |
| ---------- | ----------- | ------------ | --- | --- | --- | --- | --- | --- |
32

2.2 Basic CSS
3. Styling the Button
33

| 2.2 | Basic CSS |     |     |     |     |     |     |
| --- | --------- | --- | --- | --- | --- | --- | --- |
3. Styling the Button
| After   | updating | the code  | and    | saving   | it, we | refresh | the |
| ------- | -------- | --------- | ------ | -------- | ------ | ------- | --- |
| webpage | and      | get a new | result | as shown | here.  |         |     |
34

| 2.2 | Basic CSS |     |     |     |     |     |
| --- | --------- | --- | --- | --- | --- | --- |
4. Metadata
In the head of the index.html file, under the <title> tag, we add the following two lines.
1) we also add the <meta> tag that makes your web page responsive in any web browser
| (including |     | mobile | web browser). |     |     |     |
| ---------- | --- | ------ | ------------- | --- | --- | --- |
<meta name="viewport" content="width=device-width, initial-scale=1">
The <meta> tag provides metadata about the HTML document. Metadata will not be
displayed on the page, but provides useful information to the browser such as how to
| Display | the      | content. |           |       |     |     |
| ------- | -------- | -------- | --------- | ----- | --- | --- |
| 2) We   | also add | the      | following | line: |     |     |
<link rel="icon" href="data:,">
To prevent requests from the browser to the ESP32 about the favicon. The favicon is
| the | shortcut | icon | that appears | on the | web browser | tab. |
| --- | -------- | ---- | ------------ | ------ | ----------- | ---- |
Then, our complete index.html file is shown in the next page.
35

2.2 Basic CSS
4. Metadata
36

| 2.2 | Basic CSS |     |     |     |     |     |     |
| --- | --------- | --- | --- | --- | --- | --- | --- |
4. Metadata
| After   | updating | the code  | and    | saving   | it, we | refresh | the |
| ------- | -------- | --------- | ------ | -------- | ------ | ------- | --- |
| webpage | and      | get a new | result | as shown | here.  |         |     |
37

3. ESP32 as a Local Web Server to
Control Actuators
In this section, we will learn how to create a simple web server with the ESP32 to
control outputs. The web server we will build can be accessed with any device that as a
browser: smartphone, tablet, laptop, on the local network. This section consists of
3.1 Building ESP32 as a Local Web Server
3.2 ESP32 Web Server to Control Outputs
3.3 Code Explanation
38

| 3.1 | Building ESP32 as a Local Web Server |     |     |     |     |     |     |     |
| --- | ------------------------------------ | --- | --- | --- | --- | --- | --- | --- |
1. Web Server
| How | the ESP32 |     | uses this: |        |          |        |        |     |
| --- | --------- | --- | ---------- | ------ | -------- | ------ | ------ | --- |
|     | a) We     | can | run a web  | server | directly | on the | ESP32. |     |
b) This allows the ESP32 to “host” a web page that you can access from your phone
|     | or  | computer | to control | outputs |     | or view | sensor | data. |
| --- | --- | -------- | ---------- | ------- | --- | ------- | ------ | ----- |
39

| 3.1 Building ESP32 as a Local Web Server |     |     |     |     |     |     |     |
| ---------------------------------------- | --- | --- | --- | --- | --- | --- | --- |
2. ESP32 as a Web Server
Let us take a look at a practical example with an IoT device called ESP32 that acts as a
| web server | in        | the      | local network. |         |       |         |     |
| ---------- | --------- | -------- | -------------- | ------- | ----- | ------- | --- |
| 1) The     | Local     | Network: |                |         |       |         |     |
| a)         | The ESP32 |          | connects       | to your | Wi-Fi | router. |     |
b) Your computer or smartphone connects to the same router/access point.
| c)  | As a | result, | all devices | are on | the | same local | network. |
| --- | ---- | ------- | ----------- | ------ | --- | ---------- | -------- |
40

3.1 Building ESP32 as a Local Web Server
2. ESP32 as a Web Server
2) The Interaction:
a) You type the ESP32’s unique IP address into your browser on a client computer.
| b) Your | browser | sends | an HTTP | Request | directly | to the | ESP32. |
| ------- | ------- | ----- | ------- | ------- | -------- | ------ | ------ |
c) The ESP32 processes the request and sends back an HTTP Response.
d) As a result, your browser displays the web page, sensor data, or controls sent by
| the | ESP32. |     |     |     |     |     |     |
| --- | ------ | --- | --- | --- | --- | --- | --- |
41

3.2 ESP32 Web Server to Control Outputs
1. Project Outline
To build a web server on the ESP32 that hosts a web page with buttons to control two
LEDs.
42

3.2 ESP32 Web Server to Control Outputs
1. Project Outline
| 1) Project | Goal: |     |     |     |     |
| ---------- | ----- | --- | --- | --- | --- |
• To build a web server on the ESP32 that hosts a web page with buttons to control
| two       | LEDs.  |     |     |     |     |
| --------- | ------ | --- | --- | --- | --- |
| 2) How It | Works: |     |     |     |     |
a) Connect: The ESP32 (server) and your computer/phone (client) must be on the
| same | Wi-Fi | network. |     |     |     |
| ---- | ----- | -------- | --- | --- | --- |
b) Access: Open a web browser on your computer/phone and type in the ESP32’s IP
address.
c) Control: Click the buttons on the web page to instantly turn the LEDs (connected
| to GPIOs  | 26            | & 27) | ON or OFF. |     |     |
| --------- | ------------- | ----- | ---------- | --- | --- |
| 3) Beyond | this Example: |       |            |     |     |
• This is a foundational project. The LEDs can easily be replaced by relays, motors,
| or any | other | actuator | you want | to control | remotely. |
| ------ | ----- | -------- | -------- | ---------- | --------- |
43

3.2 ESP32 Web Server to Control Outputs
1. Project Outline
44

3.2 ESP32 Web Server to Control Outputs
1. Project Outline
1) Step 1: On a browser (at Client), the user enters the IP address of the ESP32.
Clients HTTP Request
(Computer/
GET / HTTP/1.1
Mobile Phone) Host: 192.168.43.164
ESP32
27
26
Long leg Long leg
LED1 LED2
Short leg Short leg
330 330
Clients
(Computer/
HTTP Response Pin GND of ESP32
Mobile Phone)
HTTP/1.1 200 OK
HTML Code
45

3.2 ESP32 Web Server to Control Outputs
1. Project Outline
2) Step 2: On a browser (at Client), if the user press the ON button of the LED1, the
LED1 will be on. The web page will be revised: LED1 state = On and its button is
OFF.
Clients
(Computer/
Mobile Phone)
46
P i n G N
E
D
S
o
P
f
3 2
2
2
E
7
6
S P 3 2
L
S
o
L
h
n
o
3
g
Er
3
l
Dt
l
0
e
1e
g
g
L
S
o
L
h
n
o
3
g
Er
3
Dt
0
l
l
e
2e
g
g
HTTP Request
GET /26/on HTTP/1.1
Host: 192.168.43.164
Clients
HTTP Response
(Computer/
HTTP/1.1 200 OK
Mobile Phone)
HTML Code

3.2 ESP32 Web Server to Control Outputs
1. Project Outline
3) Step 3: On a browser (at Client), if the user press the OFF button of the LED1, the
LED1 will be off. The web page will be revised: LED1 state = Off and its button is
ON.
Clients HTTP Request
(Computer/
GET /26/off HTTP/1.1
Mobile Phone) Host: 192.168.43.164
ESP32
27
26
Long leg Long leg
LED1 LED2
Short leg Short leg
330 330
Clients
HTTP Response
(Computer/
Pin GND of ESP32
HTTP/1.1 200 OK
Mobile Phone)
HTML Code
47

3.2 ESP32 Web Server to Control Outputs
1. Project Outline
4) Step 4: On a browser (at Client), if the user press the ON button of the LED2, the
LED2 will be on. The web page will be revised: LED2 state = On and its button is
OFF.
Clients HTTP Request
(Computer/
GET /27/on HTTP/1.1
Mobile Phone) Host: 192.168.43.164
ESP32
27
26
Long leg Long leg
LED1 LED2
Short leg Short leg
330 330
Clients
HTTP Response
(Computer/
Pin GND of ESP32
HTTP/1.1 200 OK
Mobile Phone)
HTML Code
48

3.2 ESP32 Web Server to Control Outputs
1. Project Outline
5) Step 5: On a browser (at Client), if the user press the OFF button of the LED2, the
LED2 will be off. The web page will be revised: LED2 state = Off and its button is
ON.
Clients HTTP Request
(Computer/
GET /27/off HTTP/1.1
Mobile Phone) Host: 192.168.43.164
ESP32
27
26
Long leg Long leg
LED1 LED2
Short leg Short leg
330 330
Clients
HTTP Response
(Computer/
Pin GND of ESP32
HTTP/1.1 200 OK
Mobile Phone)
HTML Code
49

3.2 ESP32 Web Server to Control Outputs
2. Web Page Design
Our HTML code is similar to what we have designed previously.
1) Case: The LED is OFF and the ON button is active.
50

3.2 ESP32 Web Server to Control Outputs
2. Web Page Design
Our HTML code is similar to what we have designed previously.
2) Case: The LED is ON and the OFF button is active.
51

3.2 ESP32 Web Server to Control Outputs
3. Schematic
We connect two LEDs to ESP32 as shown in the following schematic diagram – with one
LED connected to GPIO 26, and another to GPIO 27.
|     | E S P 3 | 2   |     |     |     |
| --- | ------- | --- | --- | --- | --- |
2 7
2 6
|           |               |         | L o n g |   l e g | L o n g   l e g |
| --------- | ------------- | ------- | ------- | ------- | --------------- |
|           |               |         | L Er Dt | 1e      | L Er Dt 2e      |
|           |               |         | S h o   |   l g   | S h o   l g     |
|           |               |         | 3 3     | 0       | 3 3 0           |
| P i n   G | N D   o f   E | S P 3 2 |         |         |                 |
52

3.2 ESP32 Web Server to Control Outputs
4. Arduino Code
The Arduino code “WebServer_ControlOutputs.ino” will ask ESP32 to sent a HTTP
response message when it receives the HTTP request from a client (web browser). In side
this message, there is the HTML body that we have written in the previous section. The
code explanation will be provided later. Please follow the following steps.
| 1) Write | this code | in your | Arduino | IDE. |
| -------- | --------- | ------- | ------- | ---- |
2) You have to fill in your SSID and Password of your access point.
| 3) Upload | the code | to your | ESP32. |     |
| --------- | -------- | ------- | ------ | --- |
53

3.2 ESP32 Web Server to Control Outputs
4. Arduino Code
54

3.2 ESP32 Web Server to Control Outputs
4. Arduino Code
55

3.2 ESP32 Web Server to Control Outputs
4. Arduino Code
56

3.2 ESP32 Web Server to Control Outputs
4. Arduino Code
• To turn the LED on or off
depending on the HTTP Request.
• Set the state of each LED.
57

3.2 ESP32 Web Server to Control Outputs
4. Arduino Code
HTML File
58

3.2 ESP32 Web Server to Control Outputs
HTML File
4. Arduino Code
59

3.2 ESP32 Web Server to Control Outputs
5. Demonstration
| To see | the result, | please | follow | these | steps. |     |     |
| ------ | ----------- | ------ | ------ | ----- | ------ | --- | --- |
1) When finishing uploading the code to ESP32, the serial monitor will show the IP
| address | of ESP32 | which | right | now | is working | as a web | server. |
| ------- | -------- | ----- | ----- | --- | ---------- | -------- | ------- |
2) Connect your computer/phone to the same access point (that ESP32 is connecting to).
On a web browser, type the IP address (of ESP32) on the URL and press the Enter.
You will see this web page. Clicking the buttons will turn the LEDs on/off.
60

3.2 ESP32 Web Server to Control Outputs
5. Demonstration
| The demonstration | video | is shown | below. |
| ----------------- | ----- | -------- | ------ |
61

3.3 Code Explanation
| Mainly     | the code | consists        | of the | following | parts. |
| ---------- | -------- | --------------- | ------ | --------- | ------ |
| 1) Set     | ESP32    | as a webserver. |        |           |        |
| 2) Connect | to       | the access      | point. |           |        |
62

3.3 Code Explanation
3) Listen to a client and receive the HTTP request (stored it in the variable named header)
Note:
• At the first time when the user enters the IP address of ESP32 at a browser of the client,
the client will send a HTTP request: “GET / /HTTP1.1” to the ESP32.
• Later, after the client receive the HTTP response including the HTML source code, our
| browser | will display | the webpage. |     |     |     |
| ------- | ------------ | ------------ | --- | --- | --- |
• If we click the ON button of the pin 26, there will be the text “GET /26/on” in the
| HTTP | request; | turn the | LED at | pin 26 | on. |
| ---- | -------- | -------- | ------ | ------ | --- |
• If we click the OFF button of the pin 26, there will be the text “GET /26/off” in the
| HTTP | request; | turn the | LED at | pin 26 | off. |
| ---- | -------- | -------- | ------ | ------ | ---- |
• If we click the ON button of the pin 27, there will be the text “GET /27/on” in the
| HTTP | request; | turn the | LED at | pin 27 | on. |
| ---- | -------- | -------- | ------ | ------ | --- |
• If we click the OFF button of the pin 27, there will be the text “GET /27/off” in the
| HTTP | request; | turn the | LED at | pin 27 | off. |
| ---- | -------- | -------- | ------ | ------ | ---- |
63

3.3 Code Explanation
4) Check whether the HTTP request stores “GET /26/on”, “GET /26/0ff”, “GET /27/on”,
| or “GET | /27/off”. | Then | turn on/off | the LED | correspondingly. |         |                     |           |        |           |          |      |
| ------- | --------- | ---- | ----------- | ------- | ---------------- | ------- | ------------------- | --------- | ------ | --------- | -------- | ---- |
|         |           |      |             |         |                  | The     | .indexof()          | function  |        | is        | to check |      |
|         |           |      |             |         |                  | whether | we                  | have      | the    | specified |          | text |
|         |           |      |             |         |                  | in the  | specified           | string    |        | variable. |          |      |
|         |           |      |             |         |                  | The     | header.indexof(“GET |           |        |           | /26/on”) |      |
|         |           |      |             |         |                  | command | will                | return:   |        |           |          |      |
|         |           |      |             |         |                  | • >=0   | if there            | is        | “GET   | /26/on”   |          | in   |
|         |           |      |             |         |                  | the     | header              | variable. |        |           |          |      |
|         |           |      |             |         |                  | • -1    | if there            | is no     | “GET   | /26/on”   |          | in   |
|         |           |      |             |         |                  | the     | header              | variable. |        |           |          |      |
|         |           |      |             |         |                  | where   | here,               | the       | header |           | variable |      |
|         |           |      |             |         |                  | store   | the HTTP            | request   |        | message.  |          |      |
64

3.3 Code Explanation
5) Send the HTTP response message (including the HTML body) to the client (Line 99-
133).
• The variable name client is used to represent the current client that is connecting to
| ESP32. | It has | been | defined | in Line | 56. |
| ------ | ------ | ---- | ------- | ------- | --- |
• The client.println() function will send the message inside the “” to the client. We
can notice that a series of texts sent by the client.println() function is the HTTP
| response | message. |     |     |     |     |
| -------- | -------- | --- | --- | --- | --- |
65

4. ESP32 as a Local Web Server to
Monitor Sensor Data
This section consists of
4.1 ESP32 Web Server to Monitor Sensor Data
4.2 Code Explanation
66

4.1 ESP32 Web Server to Monitor Sensor Data
1. Project Outline
To build a web server on the ESP32 that displays readings from a potentiometer
| (connected | to pin | A0). |
| ---------- | ------ | ---- |
67

4.1 ESP32 Web Server to Monitor Sensor Data
1. Project Outline
| 1) Project | Goal: |     |     |
| ---------- | ----- | --- | --- |
• To build a web server on the ESP32 that displays readings from a potentiometer
| (connected |        | to pin | A0). |
| ---------- | ------ | ------ | ---- |
| 2) How It  | Works: |        |      |
a) Connect: The ESP32 (server) and your computer/phone (client) must be on the
| same | Wi-Fi | network. |     |
| ---- | ----- | -------- | --- |
b) Access: Open a web browser and type in the ESP32’s IP address.
c) Monitor: The web page will display the real-time value from the potentiometer.
| 3) Beyond | this | Example: |     |
| --------- | ---- | -------- | --- |
• This project is a template for monitoring any sensor. You can easily add more
sensors (temperature, humidity, etc.) and display all their data on one dashboard.
68

4.1 ESP32 Web Server to Monitor Sensor Data
1. Project Outline
69

4.1 ESP32 Web Server to Monitor Sensor Data
1. Project Outline
1) Step 1: On a browser (at Client), the user enters the IP address of the ESP32.
Clients HTTP Request
(Computer/
GET   /  HTTP/1.1
Mobile Phone) Host: 192.168.43.164
|     | P i n   3 | v 3   o f   E   | S P 3 2 E | S P 3 2 |
| --- | --------- | --------------- | --------- | ------- |
|     | P         | o t e n t i o m | e t e r   |         |
|     |           |                 | A         | 0       |
Clients
(Computer/
HTTP Response
| Mobile Phone) |     |     | P i n   G N | D   o f   E S P 3 2 |
| ------------- | --- | --- | ----------- | ------------------- |
HTTP/1.1  200  OK
HTML Code
70

4.1 ESP32 Web Server to Monitor Sensor Data
1. Project Outline
2) Step 2: The user rotate the knob of the potentiometer to change its value. Thereafter,
the user presses the refresh button on the browser. The web page will update the
potentiometer value.
HTTP Request
Clients
GET / HTTP/1.1
(Computer/
Host: 192.168.43.164
Mobile Phone)
Pin 3v3 of ESP32 ESP32
Potentiometer
A0
Clients
(Computer/ HTTP Response
Pin GND of ESP32
Mobile Phone)
HTTP/1.1 200 OK
HTML Code
71

4.1 ESP32 Web Server to Monitor Sensor Data
2. Web Page Design
In this project, we will display the sensor data in a table in a web page. Our HTML code
is similar to the previous one except we create a table consisting of this two steps.
(More details can be found from here: https://www.w3schools.com/html/html_tables.asp)
1) In the <style> tags, we will define the style of our table as follows, where we set up
the table border width to 1 pixel and locate the table at the center of the page.
72

4.1 ESP32 Web Server to Monitor Sensor Data
2. Web Page Design
2) In the <body> tags, we create a table by using the following tags.
| • The | <table> | tag | defines | an HTML | table. |
| ----- | ------- | --- | ------- | ------- | ------ |
•
The <th> tag defines the table header. By default, the text in <th> elements are bold
| and   | centered. |         |     |      |     |
| ----- | --------- | ------- | --- | ---- | --- |
| • The | <tr> tag  | defines | a   | row. |     |
• The <td> tag defines a cell in a row. By default, the text in <td> elements are regular
| and       | left-aligned. |       |          |        |     |
| --------- | ------------- | ----- | -------- | ------ | --- |
| We create | the           | table | as shown | below. |     |
73

4.1 ESP32 Web Server to Monitor Sensor Data
2. Web Page Design
| Our complete | HTML | code | is shown | below. |
| ------------ | ---- | ---- | -------- | ------ |
74

4.1 ESP32 Web Server to Monitor Sensor Data
2. Web Page Design
75

4.1 ESP32 Web Server to Monitor Sensor Data
3. Schematic
We connect a potentiometer to the pin A0 of ESP32 as shown in the following schematic
diagram.
| P i | n   3 v 3   | o f   E S P | 3 2 E S P | 3 2 |
| --- | ----------- | ----------- | --------- | --- |
|     | P o t e     | n t i o m e | t e r     |     |
A 0
|     |     | P i | n   G N D   o f |   E S P 3 2 |
| --- | --- | --- | --------------- | ----------- |
76

4.1 ESP32 Web Server to Monitor Sensor Data
4. Arduino Code
The Arduino code “WebServer_MonitorSensor.ino” will ask ESP32 to sent a HTTP
response message when it receives the HTTP request from a client (web browser). In side
this message, there is the HTML body (including the potentiometer value) that we have
written in the previous section. The code explanation will be provided later. Please follow
| the following | steps.    |         |         |      |
| ------------- | --------- | ------- | ------- | ---- |
| 1) Write      | this code | in your | Arduino | IDE. |
2) You have to fill in your SSID and Password of your access point.
| 3) Upload | the code | to your | ESP32. |     |
| --------- | -------- | ------- | ------ | --- |
77

4.1 ESP32 Web Server to Monitor Sensor Data
4. Arduino Code
78

4.1 ESP32 Web Server to Monitor Sensor Data
4. Arduino Code
79

4.1 ESP32 Web Server to Monitor Sensor Data
4. Arduino Code
80

4.1 ESP32 Web Server to Monitor Sensor Data
4. Arduino Code
HTML File
81

4.1 ESP32 Web Server to Monitor Sensor Data
4. Arduino Code
82

4.1 ESP32 Web Server to Monitor Sensor Data
5. Demonstration
| To see | the | result, | please |     | follow | these | steps. |     |     |     |
| ------ | --- | ------- | ------ | --- | ------ | ----- | ------ | --- | --- | --- |
1) When finishing uploading the code to ESP32, the serial monitor will show the IP
| address |     | of ESP32 |     | which | right | now | is  | working | as a web | server. |
| ------- | --- | -------- | --- | ----- | ----- | --- | --- | ------- | -------- | ------- |
2) Connect your computer/phone to the same access point (that ESP32 is connecting to).
On a web browser, type the IP address (of ESP32) on the URL and press the Enter.
You will see this web page show the potentiometer value. To update the value, we
| must | press | the | refresh |     | button. |     |     |     |     |     |
| ---- | ----- | --- | ------- | --- | ------- | --- | --- | --- | --- | --- |
83

4.1 ESP32 Web Server to Monitor Sensor Data
5. Demonstration
| The demonstration | video | is shown | below. |
| ----------------- | ----- | -------- | ------ |
84

4.2 Code Explanation
The Arduino code of this project is quite similar to the previous one. The main difference
is in the HTML body where we send the potentiometer value (read from the pin A0) along
| with the | HTML | code | in Line | 82: |
| -------- | ---- | ---- | ------- | --- |
85

5. ESP32 as a Client to an IoT Cloud
Platform
This section consists of
5.1 IoT Cloud Platform
5.2 Showing Sensor Data on ThingSpeak
5.3 Code Explanation
86

5.1 IoT Cloud Platforms: Connecting to the World
| 1)  | What |     | are | they? |     |     |     |     |
| --- | ---- | --- | --- | ----- | --- | --- | --- | --- |
• Specialized web services designed to ingest, store, visualize, and manage data from
|     |     | IoT | devices. |      |     |     |     |     |
| --- | --- | --- | -------- | ---- | --- | --- | --- | --- |
| 2)  | Why | use |          | one? |     |     |     |     |
• It is the easiest way to monitor and control your devices securely over the internet,
|     |     | from | anywhere |          | in      | the world. |     |     |
| --- | --- | ---- | -------- | -------- | ------- | ---------- | --- | --- |
| 3)  | How | do   | we       | connect? |         |            |     |     |
|     | a)  | The  | ESP32    |          | acts as | a client.  |     |     |
b) It sends data to the platform’s API (Application Programming Interface), which is
|     |         | like | a          | special, | secure | mailbox | for your | data. |
| --- | ------- | ---- | ---------- | -------- | ------ | ------- | -------- | ----- |
| 4)  | Popular |      | Platforms: |          |        |         |          |       |
• ThingSpeak, Ubidot, Netpie (Nectec), Google, IBM Watson, AWS, Cisco, Kaa,
|     |     | Oracle, |     | Thingworx, |     | etc. |     |     |
| --- | --- | ------- | --- | ---------- | --- | ---- | --- | --- |
87

5.2 Sending ESP32 Data to the ThingSpeak Cloud
1. Project Outline
To send sensor data from an ESP32 to the ThingSpeak cloud platform for remote
| monitoring | from | anywhere. |
| ---------- | ---- | --------- |
88

5.2 Sending ESP32 Data to the ThingSpeak Cloud
1. Project Outline
| 1)  | Project |     | Goal: |     |     |     |     |     |     |     |     |
| --- | ------- | --- | ----- | --- | --- | --- | --- | --- | --- | --- | --- |
• To send sensor data from an ESP32 to the ThingSpeak cloud platform for remote
|     |     | monitoring |     |     | from |     | anywhere. |     |     |     |     |
| --- | --- | ---------- | --- | --- | ---- | --- | --------- | --- | --- | --- | --- |
2) Architecture:
|     | •       | Client: |          | ESP32      |     | (reading |     | a potentiometer |          | on pin | A0) |
| --- | ------- | ------- | -------- | ---------- | --- | -------- | --- | --------------- | -------- | ------ | --- |
|     | •       | Server: |          | ThingSpeak |     |          | IoT | Cloud           | Platform |        |     |
| 3)  | Process |         | (Repeats |            |     | every    | 10  | seconds):       |          |        |     |
a) Read: The ESP32 reads the current value from the potentiometer and a random
number.
b) Send: The ESP32 sends two values every 10 seconds via an HTTP Request to
|     |     | your | unique |     | ThingSpeak |     |     | channel | API. |     |     |
| --- | --- | ---- | ------ | --- | ---------- | --- | --- | ------- | ---- | --- | --- |
c) Visualize: ThingSpeak receives these two values, stores them, and automatically
|     |     | plots | them |     | on  | two | charts. |     |     |     |     |
| --- | --- | ----- | ---- | --- | --- | --- | ------- | --- | --- | --- | --- |
Result: A cloud-hosted dashboard that you can access from any browser to monitor your
| sensor |     | data | in  | real-time. |     |     |     |     |     |     |     |
| ------ | --- | ---- | --- | ---------- | --- | --- | --- | --- | --- | --- | --- |
89

5.2 Sending ESP32 Data to the ThingSpeak Cloud
1. Project Outline
90

5.2 Sending ESP32 Data to the ThingSpeak Cloud
1. Project Outline
1) ESP32 send a HTTP
request (potentiometer and a
random number).
2) ThingSpeak sends back a
HTTP response.
A Web Client
ThingSpeak
Server
1) Browser sends a HTTP
request.
User using
a Web Browser
2) ThingSpeak sends back a
A Web Client
HTTP response including the
HTML code.
91

5.2 Sending ESP32 Data to the ThingSpeak Cloud
1. Project Outline
| The key | in this | project | is: |     |     |     |     |
| ------- | ------- | ------- | --- | --- | --- | --- | --- |
1) ESP32 sends the HTTP Get message to ThingSpeak. This message includes the
| potentiometer |      | value       | and | a random   | number. |        |            |
| ------------- | ---- | ----------- | --- | ---------- | ------- | ------ | ---------- |
| 2) The        | HTTP | Get message |     | is in this | format  | (it is | a string): |
https://api.thingspeak.com/update?api_key=YourAPIkey&field1=250&field2=40
where YourAPIkey is your ThingSpeak API key, 250 is your potentiometer value, and
| 40  | is your | random | number. |     |     |     |     |
| --- | ------- | ------ | ------- | --- | --- | --- | --- |
92

5.2 Sending ESP32 Data to the ThingSpeak Cloud
2. Sign up ThingSpeak and Create a Channel
ThingSpeak has a free API that allows you to store and retrieve data using HTTP. In this
tutorial, you will use the ThingSpeak API to publish and visualize data in charts from
anywhere. The following steps guide you wo create a ThingSpeak channel.
1) Create a ThingSpeak account.
2) Create a new channel by clicking on the New Channel button.
93

5.2 Sending ESP32 Data to the ThingSpeak Cloud
|     | 2. Sign up ThingSpeak |       |        |          |      |         |     | and Create a Channel |     |     |     |
| --- | --------------------- | ----- | ------ | -------- | ---- | ------- | --- | -------------------- | --- | --- | --- |
| 3)  | In your               |       | new    | channel, |      | fill in |     |                      |     |     |     |
|     | •                     | Name: | Sensor |          | Data |         |     |                      |     |     |     |
•
|     |       | Field | 1: Potentiometer |       |      |        |       |        |     |       |       |
| --- | ----- | ----- | ---------------- | ----- | ---- | ------ | ----- | ------ | --- | ----- | ----- |
|     | •     | Field | 2: Random        |       |      | Number |       |        |     |       |       |
|     | The   | other | fields           |       | are  | blank. | We    | fill   | in  | Field | 1 and |
|     | Field | 2     | since            | we    | will | show   | two   | sensor |     | data. | Make  |
|     | sure  | that  | the              | boxes |      | after  | Field | 1      | and | Field | 2 are |
checked.
| 4)  | Click | the | save | button |     | at the | bottom | of  | this | page. |     |
| --- | ----- | --- | ---- | ------ | --- | ------ | ------ | --- | ---- | ----- | --- |
94

5.2 Sending ESP32 Data to the ThingSpeak Cloud
| 2. Sign up ThingSpeak |     |     |     | and Create a Channel |
| --------------------- | --- | --- | --- | -------------------- |
5) You will go to your ThingSpeak channel (Sensor Data). There are many tabs. When
you click the private view tab, you will see the Filed 1 chart and Field 2 chart which
| will show | the data | sent | from ESP32. |     |
| --------- | -------- | ---- | ----------- | --- |
6) Click on the API Keys tab, to see your Write API key. Record it since we will use it in
| the Arduino | code. | Now, | we are | done. |
| ----------- | ----- | ---- | ------ | ----- |
95

5.2 Sending ESP32 Data to the ThingSpeak Cloud
3. Schematic
We connect a potentiometer to the pin A0 of ESP32 as shown in the following schematic
diagram.
| P i | n   3 v 3   | o f   E S P | 3 2 E S P | 3 2 |
| --- | ----------- | ----------- | --------- | --- |
|     | P o t e     | n t i o m e | t e r     |     |
A 0
|     |     | P i | n   G N D   o f |   E S P 3 2 |
| --- | --- | --- | --------------- | ----------- |
96

5.2 Sending ESP32 Data to the ThingSpeak Cloud
4. Arduino Code
The Arduino code “WebClient_ThingSpeak.ino” will ask ESP32 to sent two values
(potentiometer value and a random number) to ThingSpeak. Please revise the code as
| follows  | and upload | to your | ESP32   |      |
| -------- | ---------- | ------- | ------- | ---- |
| 1) Write | this code  | in your | Arduino | IDE. |
2) You have to fill in your SSID and Password of your access point.
| 3) Put    | your Write | API Key  | from | ThingSpeak. |
| --------- | ---------- | -------- | ---- | ----------- |
| 4) Upload | the code   | to ESP32 |      |             |
97

5.2 Sending ESP32 Data to the ThingSpeak Cloud
4. Arduino Code
98

5.2 Sending ESP32 Data to the ThingSpeak Cloud
4. Arduino Code
99

5.2 Sending ESP32 Data to the ThingSpeak Cloud
4. Arduino Code
100

5.2 Sending ESP32 Data to the ThingSpeak Cloud
4. Arduino Code
101

5.2 Sending ESP32 Data to the ThingSpeak Cloud
5. Demonstration
1) When finishing uploading the code to ESP32, ESP32 will try to connect the WiFi
access point.
2) ESP32 sends the HTTP request message to ThingSpeak every 10 seconds.
3) ThingSpeak receives the message, send a HTTP response back, and update the charts.
102

5.2 Sending ESP32 Data to the ThingSpeak Cloud
5. Demonstration
| A demonstration | video | is shown | below. |
| --------------- | ----- | -------- | ------ |
103

5.3 Code Explanation
| Mainly     | the code | consists   | of the | following | parts. |
| ---------- | -------- | ---------- | ------ | --------- | ------ |
| 1) Specify | your     | ThingSpeak |        | API key.  |        |
2) Set ESP32 as a WiFi client and a HTTP client (to be able to send a HTTP Get
request).
| 3) Create | a HTTP | request | message. |     |     |
| --------- | ------ | ------- | -------- | --- | --- |
104

5.3 Code Explanation
4) Call the begin method on the http object to store this URL on the http object.
| 5) Send | the HTTP | request | by the | GET | method. |
| ------- | -------- | ------- | ------ | --- | ------- |
where httpResponseCode stores the returned code from ThingSpeak.
105

6. Advanced Topics for ESP32 Web
Servers and Clients
106

Advanced Topics for ESP32 Web Servers
The following topics could be useful for your work in the future.
1. You might create a password to log into the ESP32 web server:
https://randomnerdtutorials.com/esp32-esp8266-web-server-http-authentication/
2. You might consider the web socket approach to automatically update the data on your
web page:
https://randomnerdtutorials.com/esp32-websocket-server-arduino/
3. You might consider the asynchronous web server approach such that no information is
shown in the URL of the web browser (which is not secure):
https://randomnerdtutorials.com/esp32-async-web-server-espasyncwebserver-library/
4. You might implement your ESP32 web to access from anywhere (globally):
https://microcontrollerslab.com/accessing-esp32-web-server-anywhere-world-
esp8266/
107

Advanced Topics for ESP32 Web Clients
The following topics could be useful for your work in the future.
| 1. You | might | find more | examples | to use | the HTTP | GET | method: |
| ------ | ----- | --------- | -------- | ------ | -------- | --- | ------- |
https://randomnerdtutorials.com/esp32-http-get-open-weather-map-thingspeak-
arduino/
| 2. You | might | find more | examples | to use | the HTTP | POST | method: |
| ------ | ----- | --------- | -------- | ------ | -------- | ---- | ------- |
https://randomnerdtutorials.com/esp32-http-post-ifttt-thingspeak-arduino/
| 3. You | might | set ESP32 | to send | an email: |     |     |     |
| ------ | ----- | --------- | ------- | --------- | --- | --- | --- |
https://randomnerdtutorials.com/esp32-send-email-smtp-server-arduino-ide/
4. You might send your data to other IoT cloud platforms such as Google, AWS, etc.
108

Questions?
109
