# Fyrryx - a EEERover project

This GitHub page is secondary to the [google docs](https://docs.google.com/document/d/1JxvHMA5bM8CIvgcVcvtxcrbAdgQVOpjjdfhHl-o1c70/edit?usp=sharing). This should primarily be used for code, but will contain useful information on the project timeframe and plan.

## Timeframe

![image](https://github.com/saturn691/Fyrryx/assets/113542065/a43d8117-d57a-4dd4-93b6-6bfc5c188b2c)
![image](https://github.com/saturn691/Fyrryx/assets/113542065/40281e09-33d9-4ecf-9007-517971ebe35e)

## How to use this page?

If you are new to GitHub, here's how to get, make and upload changes into the server.

1. Install [git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)
2. Clone the repository to your local computer by running these commands in the terminal of your working directory:
```
git clone https://github.com/saturn691/Fyrryx/
```
Alternatively, you can press "<> Code" to download the repository.
![image](https://github.com/saturn691/Fyrryx/assets/113542065/d7d978fd-bf98-4dcf-bfde-b7700f0c0ab8)
3. Run these commands in the terminal of the folder that you are working on (Fyrryx). This saves any changes to your local system. Replace "BRANCH_NAME" with a suitable name (e.g. remote-car or magnetic-field)
```
git checkout main
git pull origin main
git checkout -b BRANCH_NAME
```
4. When you are ready to commit changes, run these commands
```
git add .
git commit -m "YOUR_MESSAGE"
git push origin BRANCH_NAME
```
5. Come back to GitHub and press "Compare & pull request"
6. Leave a comment for good practice so we know what you've done
7. Press "Create pull request"
8. Leave a message on the group chat and we'll vote to approve the changes.

## Development of code

There are two parts to this- the server and the client. How does this work? We use a protocol called UDP instead of sending HTTP requests. This ensures the fastest connection between the server and the client. 

### Dependencies

- pygame (for handling controller)
- ArduinoJson.h

To resolve, run this command in the terminal. If you don't have pip installed there are guides for installing pip (the python module installer).
```
pip install pygame
```
### Controller

Controller code is developed in Python with OOP techniques. Data is sent over via the Fyrryx UDP Protocol. For convenience, your workspace should be Fyrryx/controller/

### Server

Server code is developed in CPP with OOP techniques. Data is sent over via the Fyrryx UDP Protocol. Your workspace must be Fyrryx/server/ or it will NOT compile. Place all .cpp files in /src and all function definition in /src/headers. To develop code for a feature

1. Create a new .cpp file in /src/ with a meaningful name (e.g. name.cpp)
2. Create a .h file in /src/headers/ with the same name (e.g. name.h)
3. Add these lines of code
```
// name.h

#ifndef _RECEIVER_h
#define _RECEIVER_h
#include <Arduino.h>

// Any other includes, and your function definitions

#endif
```
```
// name.cpp

#include <headers/name.h>
```
```
// main.ino

#include <headers/name.h>
```

## Useful links

Google docs: https://docs.google.com/document/d/1JxvHMA5bM8CIvgcVcvtxcrbAdgQVOpjjdfhHl-o1c70/edit?usp=sharing

Microsoft teams: https://teams.microsoft.com/l/channel/19%3a2wmt9rLXf4xx70l7Jkldz84n94MIJ1uw8qI6J1Ydr4A1%40thread.tacv2/General?groupId=c621b226-48c8-44c9-b2c6-fa1edf2d9cd8&tenantId=2b897507-ee8c-4575-830b-4f8267c3d307

Whatsapp web: https://web.whatsapp.com
