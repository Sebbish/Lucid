#include "cred.h"


cred::cred()
{
	m.openFromFile("../../../LucidProject/Resources/Music/Elevatorfish Mono Close.ogg");
	m.setLoop(true);
	m.play();
	std::string a;
	std::string b ="                                ";
	a = '\n';
	text = "Game Design: 	     Hamza Bajwa"+a+b+"Jesper Olsson"+a+b+"Clas Brantervik"+a+a+"Writing:               	Jesper Olsson"+a+b+"Clas Brantervik"+a+a+"Graphics:            	Mattias Lindblad"+a+b+"Gustav Rosberg"+a+b+"Rebecca Nilsson"+a+b+"Johan Renkse"+a+a+"Programming:	 	Peter Bruhn"+a+b+"Sebastian Järkeborn"+a+b+"Ronny Karlsson"+a+a+"Music: 	                Victor Engström"+a+b+"Ludvig Lindeberg"+a+a+"Sound: 	                Kristoffer Eriksson"+a+b+"Victoria Täng"+a+a+"Lead Designer:       Jesper Olsson"+a+a+"Lead Programmer:  Peter Bruhn"+a+a+"Graphic Lead:         Mattias Lindblad"+a+a+"Art Director:           Gustav Rosberg"+a+a+"Sound Lead:            Kristoffer Eriksson "+a+a+"Original Concept:    Jesper Olsson"+a+a+"Project Manager:    Mattias Lindblad"+a+a+"Special Thanks to Viktor Karlsson"+a+a+b+"Credits";
	f.loadFromFile("../../../LucidProject/Resources/Dialog/ariblk.ttf");
	t.setFont(f);
	t.setString(text);
	t.setPosition(300,-t.getGlobalBounds().height);
	end = false;
}


cred::~cred()
{
}

bool cred::tick()
{
	t.setPosition(t.getPosition().x,t.getPosition().y+3);
	if(t.getPosition().y >= 1920)
		end = true;
	return end;
}

void cred::render(sf::RenderWindow &target)
{
	target.draw(t);
}
