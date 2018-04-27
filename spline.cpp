#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;
#include "k_header.hpp"

#define X 800
#define Y 800
#define BORDER 10
#define STEP 10
#define MAXPOINTS 100


int main(int argc,char ** argv){
try{//можно добавить параметры
	k_point p[100];
	k_point m[100];
	int i=0;
	int turn=0;
	int mode=0;
	RenderWindow window(VideoMode(X,Y),"Spline");
	window.clear(Color::White);
	window.display();
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed) window.close();//закрытие
			else if (event.type ==sf::Event:: MouseButtonPressed && !mode){ //кнопка нажата
				if (event.mouseButton.button == sf::Mouse::Left){
					turn=0;
					if (i==MAXPOINTS-1) throw ex(3);//throw
					p[i].x=event.mouseButton.x;
					p[i].y=event.mouseButton.y;
					while (!turn){
						Event event0;//button realissed
						while (window.pollEvent(event0)){
							if (event0.type ==Event::Closed) {window.close(); throw ex(5);}
							else if (event0.type ==sf::Event::MouseMoved){//мышка переместилась с зажатой кнопкой
								m[i].x=check_border(event0.mouseMove.x,X,BORDER)-p[i].x;
								m[i].y=check_border(event0.mouseMove.y,Y,BORDER)-p[i].y;
								window.clear(Color::White);
								draw_points(p,i+1,window,Color::Red);
								if (i!=0) draw_curve(&p[i-1],&m[i-1],2,window,Color::Red);
								draw_line(p[i],m[i]+p[i],window,Color::Green);
								draw_curve(p,m,i,window,Color::Black);
								window.display();
							} 
							else if (event0.type == sf::Event:: MouseButtonReleased && event0.mouseButton.button == sf::Mouse::Left){//кнопка отжата
								i++;
								dnd(p,m,i,window,Color::Black);
								turn=1;
							}

						}
					}
				}
			}
			else if (event.type == Event::MouseButtonPressed && mode){//кнопка нажата, режим редактирвоания
				k_point buf;
				int num;
				buf.x=event.mouseButton.x;
				buf.y=event.mouseButton.y;
				num=check_points(p,i,buf);
				if (-1!=(num=check_points(p,m,i,buf))){
					//попали в точку производной
					turn = 0;
					while (!turn){
						Event event0;
						while (window.pollEvent(event0)){
							if (event0.type ==sf::Event::MouseMoved){//мышка переместилась с зажатой кнопкой
								m[num].x=check_border(event0.mouseMove.x,X,BORDER)-p[num].x;
								m[num].y=check_border(event0.mouseMove.y,Y,BORDER)-p[num].y;
								dnd(p,m,i,window,Color::Black,Color::Green);
							} //кнопка отжата
							else if (event0.type == sf::Event:: MouseButtonReleased && event0.mouseButton.button == sf::Mouse::Left){
								turn=1;
							}//нажата D
							else if (event0.type == Event:: KeyPressed && event0.key.code == Keyboard::D){
								m[num].x=0;
								m[num].y=0;
								dnd(p,m,i,window,Color::Black,Color::Green);
								turn=1;
							}
						}
						
					}
				}
				else if (-1!=(num=check_points(p,i,buf))){
					//попали в точку кривой
					turn = 0;
					while (!turn){
						Event event0;
						while (window.pollEvent(event0)){
							if (event0.type ==sf::Event::MouseMoved){//мышка переместилась с зажатой кнопкой
								p[num].x=check_border(event0.mouseMove.x,X,BORDER);
								p[num].y=check_border(event0.mouseMove.y,Y,BORDER);
								dnd(p,m,i,window,Color::Black,Color::Green);
							}
							else if (event0.type == sf::Event:: MouseButtonReleased && event0.mouseButton.button == sf::Mouse::Left){//кнопка отжата
								turn=1;
							}
							else if (event0.type == Event::KeyPressed && event0.key.code == Keyboard::A){
								k_point buf;
								ins_point(p,p[num],num,i,MAXPOINTS);
								i--;
								ins_point(m,buf,num,i,MAXPOINTS);
								num++;
							}
							else if (event0.type == Event:: KeyPressed && event0.key.code == Keyboard::D){
								del_point(p,num,i);
								i++;
								del_point(m,num,i);
								dnd(p,m,i,window,Color::Black,Color::Green);
								turn=1;
							}
						}
						
					}
					
				}
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
				mode=mode^1;
				if (mode) dnd(p,m,i,window,Color::Black,Color::Green); else dnd(p,m,i,window,Color::Black);
			}
		}
	}
}
	catch (int i){printf("%d\n",i);}
	catch (ex a){/*a.out();*/}
	return 0;
}
