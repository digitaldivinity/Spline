struct k_point{
	double x,y;
	k_point();
	k_point(const double & x, const double & y);
	k_point operator*(double num);
	k_point operator+(k_point ob);
	k_point operator-(k_point ob);
	int operator==(k_point & ob);
	void out();
};
class ex{
	int code;
	public:
	ex(int i=0);
	void out();
};
double pow(double x,int y);
double h1(double t);
double h2(double t);
double h3(double t);
double h4(double t);
k_point polinom(k_point one,k_point two,k_point done, k_point dtwo, double t);
void ins_point(k_point * p,k_point & chto, int mesto, int & kolvo,int maximum);
void del_point(k_point * p, int mesto, int & kolvo);
double abs(double x);
int check_points(k_point * p,int amount, k_point what);
int check_points(k_point * p,k_point * m, int amount, k_point what);
void draw_points(k_point * p,int amount,RenderWindow & window,sf::Color clr);
void draw_points(k_point * p,k_point *m,int amount,RenderWindow & window,sf::Color clr);
void draw_line(k_point p1,k_point p2,RenderWindow & window, sf::Color clr);
void draw_curve(k_point * p,k_point * m, int amount, RenderWindow & window,sf::Color clr);
double check_border(double x,double window,double border);
void dnd(k_point * p,k_point *m,int amount, RenderWindow & window,Color curve);
void dnd(k_point * p,k_point *m,int amount, RenderWindow & window,Color curve,Color line);
