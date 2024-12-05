const int year=2023, month=1, day=1;
const int f_h_y=3;
const int pn=1, rn=2;
int ans = 0;

void cauculate(int y, int m, int d){
	for(int i=year; i <= y; i++){
		if(i!=y){
			if( (i % 400 == 0) || ((i % 4 == 0) && (i % 100 != 0))) ans += rn;
			else ans += pn;
		}
		else{
			for(int j=month;j<=m;j++){
				if(j!=m){
					if(j==2){
						if( (i%400==0)||((i%4==0)&&(i%100!=0)) ) ans += 1;
					}
					else{
						if(j==1 || j==3 || j==5 || j==7 || j==8 || j==10 || j==12){
							ans += 3;
						}
						else{
							ans+=2;
						}
					}
				}
				else{
					ans += d - day;
				}
			}
		}
	}
}

int main(){
	int y, m, d;
	puts("Please enter the year, month and day which separated by a space between each:\n");
	y = getint();
	m = getint();
	d = getint();
	if(y>=2023){
		if(y-year>=400){
			ans += f_h_y * (y - year);
			y -= (y - year) / 400;
		}
		cauculate(y,m,d);
	}
	ans= ans % 7;
	if (ans == 1){
		puts("Monday\n");
	}else if (ans == 2) {
		puts("Tuesday\n");
	}else if (ans == 3) {
		puts("Wednesday\n");
	}else if (ans == 4) {
		puts("Thursday\n");
	}else if (ans == 5) {
		puts("Friday\n");
	}else if (ans == 6) {
		puts("Saturday\n");
	}else if (ans == 7) {
		puts("Sunday\n");
	}
	return 0;
} 