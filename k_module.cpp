#include <stdio.h>
#include <SFML/Graphics.hpp>
using namespace sf;
struct k_point{
	double x,y;
	k_point(){
		x=y=0;
	}
	k_point(const double & x, const double & y){//not enough
		this->x=x;
		this->y=y;
	}
	k_point operator*(double num){
		k_point ob(x*num,y*num);
		return ob;
	}
	k_point operator+(k_point ob){
		k_point r(x+ob.x,y+ob.y);
		return r;
	}
	k_point operator-(k_point ob){
		k_point r(x-ob.x,y-ob.y);
		return r;
	}
	int operator==(k_point & ob){
		if (ob.x==x && ob.y ==y) return 1;
		else return 0;
	}
	void out(){
		printf("%lf %lf\n",x,y);
	}
};
class ex{
	int code;
	public:
	ex(int i=0) {code=i;}
	void out(){
		switch (code){
			
			case 1: printf("one\n"); break;
			case 2: printf("two\n"); break;
			case 3: printf("array overflow error\n"); break;
			case 5: printf("Неполный набор параметров\n"); break;
			default: printf("undef error code %d\n",code); break;
		}
	}
};
//возведение в степень
double pow(double x,int y){
	int i;
	double buf=x;
	if (y==0) return 0;
	if (y<0) throw 2; //throw
	for (i=0;i<y-1;i++){
		x*=buf;
	}
	return x;
}
double h1(double t){
	return 2*pow(t,3)-3*pow(t,2)+1;
}
double h2(double t){
	return -2*pow(t,3)+3*pow(t,2);
}
double h3(double t){
	return pow(t,3)-2*pow(t,2)+t;
}
double h4(double t){
	return pow(t,3)-pow(t,2);
}//вычисление точек
k_point polinom(k_point one,k_point two,k_point done, k_point dtwo, double t){
	return one*h1(t)+two*h2(t)+done*h3(t)+dtwo*h4(t);
}
//место - номер в массиве, количество - колво значимых элементов массива
void ins_point(k_point * p,k_point & chto, int mesto, int & kolvo,int maximum){
	if (kolvo==maximum) throw ex(40);
	if (mesto > kolvo-1) throw ex(40); //throw
	for (int i=kolvo-1;i>=mesto;i--) p[i+1]=p[i];//сдвиг	
	p[mesto]=chto;
	kolvo++;
}
//количество передается по ссылке, это важно
void del_point(k_point * p, int mesto, int & kolvo){
	if (kolvo<1) return ; //thrwo
	if (mesto>kolvo-1) throw ex(41); //throw
	for (int i=mesto;i<kolvo-1;i++){//сдвиг
		p[i]=p[i+1];
	}
	kolvo--;
}
//модуль
double abs(double x){
	if (x<0) return -x;
	else if (x==0) return 0;
	else return x;
}
int check_points(k_point * p,int amount, k_point what){
	for (int i=0;i<amount;i++){
		if (abs(p[i].x-what.x)<=8 && abs(p[i].y-what.y)<=8) return i;
	}
	return -1;
}
//поиск в массиве точки
int check_points(k_point * p,k_point * m, int amount, k_point what){
	for (int i=0;i<amount;i++){
		if (abs(p[i].x+m[i].x-what.x)<=8 && abs(p[i].y+m[i].y-what.y)<=8) return i;
	}
	return -1;
}
//отрисовка точек
void draw_points(k_point * p,int amount,RenderWindow & window,sf::Color clr){
	CircleShape shape(2,100);
	shape.setFillColor(clr);
	for (int i=0;i<amount;i++){
		shape.setPosition(p[i].x-2,p[i].y-2);
		window.draw(shape);
	}
}
//отрисовка точек
void draw_points(k_point * p,k_point *m,int amount,RenderWindow & window,sf::Color clr){
	CircleShape shape(2,100);
	shape.setFillColor(clr);
	for (int i=0;i<amount;i++){
		shape.setPosition(p[i].x+m[i].x-2,p[i].y+m[i].y-2);
		window.draw(shape);
	}
}
//отрисовка отрезка
void draw_line(k_point p1,k_point p2,RenderWindow & window, sf::Color clr){
	sf::Vertex pts[2];
	pts[0].position = sf::Vector2f(p1.x,p1.y);
	pts[1].position = sf::Vector2f(p2.x,p2.y);
	pts[0].color=clr;
	pts[1].color=clr;
	window.draw(pts, 2, sf::Lines);
}
//отрисока кривой
void draw_curve(k_point * p,k_point * m, int amount, RenderWindow & window,sf::Color clr){
	k_point buf1,buf2=p[0];
	int i;
	for (i=0;i<amount-1;i++)//внешний цикл по парам точек
	{
		for (double t=0;t<=1.01;t+=0.04){
			buf1=polinom(p[i],p[i+1],m[i],m[i+1],t);
			draw_line(buf1,buf2,window,clr);
			buf2=buf1;
		}
	}
	draw_points(&p[0],amount,window,Color::Red);
}
//проверка границ
double check_border(double x,double window,double border){
	if (x<border) return border;
	else if (x>window) return window-border;
	else return x;
}
//draw and display
void dnd(k_point * p,k_point *m,int amount, RenderWindow & window,Color curve){
	window.clear(Color::White);
	draw_curve(p,m,amount,window,curve);
	window.display();
}
void dnd(k_point * p,k_point *m,int amount, RenderWindow & window,Color curve,Color line){
	window.clear(Color::White);
	draw_curve(p,m,amount,window,curve);
	for (int i=0;i<amount;i++) draw_line(p[i],p[i]+m[i],window,line);
	draw_points(p,m,amount,window,Color::Green);
	window.display();
}

