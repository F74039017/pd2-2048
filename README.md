2048
===========================
The program is Qt Gui Application<br />
There are three modes you can choose in menu.<br />
Rank won't evaporate after the program terminated. <br />
(You can change it during game too, but the current score will be discarded.)<br />
If you need to clear it, please delete the user.db file in same directory<br />

More detail for this project, please click [here](https://terry-alu.hackpad.com/Qt-2048-dbH365v7CAG)

Environment 
--------------------------
OS: ubuntu 14.04 LTS<br />
gcc version: 4.8.2<br />
QMake version: 3.0<br />
Qt version: 5.4.0<br />

Compilation 
--------------------------
`qmake` `make`<br />
OR<br/>
Use Qt creator to compile the project<br />

Rule
--------------------------
Sum two same tiles to reach 2048.<br />

**Classic**

	You can press cont. button to continue and get higher score.

**XTile**

	There is a "X" tiles that cannot be summed.
	The scores each time you sum are 1.5 times than that of Classic mode.
	
**Survival**

	Reach 2048 within the time.
	You can get bonus time if you sum tiles which >= 16
	The scores each time you sum are 2 times than that of Classic mode.
	
After pressing cont. button, the max value of tiles is 2048. i.e two 2048 tiles can't be summed!

Architecture 
--------------------------
**Mainwindow**

	Hold central and menu bar.
	Handle modes, option and mute function settings for the game.
	Ask user to type userName.
	
**Game**

	A QGraphicsView derived class.
	Handle the game scene and index scene.
	
**IndexScene**

	Start scene after typing userName.
	Handle the rank scene.
	
**GameScene**

	Handle whole game of 2048, including animation, gameover scene...etc.
	
**Icon**

	Hold all icon setting including pixmap, glow and sound effect.
	
**Square**

	Contain QPropertyAnimation class to implement move animation. (Controled by gameScene)
	

Reference	
------------------------
[**Index background picture**]
(http://hdw.eweb4.com/out/786647.html)<br />
[**Square Photoshop tutorial**]
(https://www.youtube.com/watch?v=qaNTZyne5RY)<br />
[**Framework**]
(https://www.youtube.com/watch?v=8ntEQpg7gck&list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy)<br />
[**Music**]
(http://maoudamashii.jokersounds.com/)<br />

Too many to list all here.<br />
My Icon and squares were designed by following youtube tutorial.<br />
As for Animation and some effects, look up [here](http://doc.qt.io/qt-5/widget-classes.html) and StackOverflow.<br /> 
