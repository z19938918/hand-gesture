Mykinect* Skinect=new Mykinect();
MyJoint* axisRJoint = new MyJoint(Skinect);

MyJoint* RhandJoint = new MyJoint(Skinect);

MyJoint* ThumbRJoint = new MyJoint(Skinect);


int mean_arry_y = 0, spacing = 100, sum = 0, aver = 5, timer1 = 0, timer2 = 30,
    y=0,z=0, average_y1 = 0, average_z1 = 0, average_y2 = 0, average_z2 = 0;
double *axisR = new double(3);

double *Rhand = new double(3);
MyJoint* axisLJoint = new MyJoint(Skinect);
MyJoint* LhandJoint = new MyJoint(Skinect);
double *axisL = new double(3);
double *Lhand = new double(3);
while(1)
{		
    axisR = axisRJoint->Get_Joint(JointType::JointType_HandTipRight);		
    Rhand = RhandJoint->Get_Joint(JointType::JointType_HandRight);
    cout << ".";					
    y = y + axisR[1];
    z = z + axisR[2];		
    int key = 0;
    mean_arry_y++;
    if (mean_arry_y % aver==0) {
        
        axisL = axisLJoint->Get_Joint(JointType::JointType_HandTipLeft);
        Lhand = LhandJoint->Get_Joint(JointType::JointType_HandLeft);
        if (axisL[2] < Lhand[2] ) {
            average_y2 = average_y1;
            average_z2 = average_z1;			
            key = 1;
        }
        average_y1 = y / aver;
        average_z1 = z / aver;		
        y = 0;
        z = 0;			
    }

    if(key==1) {
        if (average_y1 >= (average_y2 + spacing) && average_z1 <= (average_z2 - spacing)) {
            cout << "窗簾開" << endl;//右上
            system("python C:\\Users\\NocturneX\\Desktop\\IOT\\iot_curtain.py outer_open");							
        }
        else if (average_y1 >= (average_y2 + spacing) && average_z1 >= (average_z2 + spacing)) {
            cout << "窗簾關" << endl;//右下
            system("python C:\\Users\\NocturneX\\Desktop\\IOT\\iot_curtain.py outer_close");				
        }
        else if (average_y1 <= (average_y2 - spacing) && average_z1 >= (average_z2 + spacing)) {
            cout << "紗簾關" << endl;//左下
            system("python C:\\Users\\NocturneX\\Desktop\\IOT\\iot_curtain.py inner_close");				
        }
        else if (average_y1 <= (average_y2 - spacing) && average_z1 <= (average_z2 - spacing)) {
            cout << "紗簾開"<< endl;//左上
            system("python C:\\Users\\NocturneX\\Desktop\\IOT\\iot_curtain.py inner_open");			
        }
        else if ( abs(average_z1- average_z2)<20 && (average_y1 - average_y2)>100) {
            cout << "搖滾樂" << endl;//右
            system("python C:\\Users\\NocturneX\\Desktop\\IOT\\iot_music.py	play_rock");
        }
        else if (abs(average_z1 - average_z2)<20 && (average_y2 - average_y1)>100) {
            cout << "抒情" << endl;//左
            system("python C:\\Users\\NocturneX\\Desktop\\IOT\\iot_music.py play_soft");
        }
        else if (abs(average_z1 - average_z2)<20 && (average_y2 - average_y1)>100) {
            cout << "抒情" << endl;//左
            system("python C:\\Users\\NocturneX\\Desktop\\IOT\\iot_music.py play_soft");
        }
        else if (abs(average_y1 - average_y2)<20 && (average_z1 - average_z2)>100) {
            cout << "台語" << endl;//下
            system("python C:\\Users\\NocturneX\\Desktop\\IOT\\iot_music.py taiwan");
        }
        Sleep(30);		
        average_y2 = 0; average_z2 = 0;
        sum = 0;
        
      }
    axisL[2] = 100;
    Lhand[2] = 0;
    //cout << axisL[2] << endl << Lhand[2] << endl;
    Sleep(30);


}