#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <raspicam/raspicam.h>
using namespace std;
#define PORT 8234

int camera()
{
    const int kpixwidth =128*10;
    const int kpixheight = 1000;
    raspicam::RaspiCam Camera; //Cmaera object
    //Open camera
    cout<<"Opening Camera..."<<endl;
    Camera.setWidth(kpixwidth );
    Camera.setHeight(kpixheight );
    Camera.setBrightness(100);
    Camera.setSharpness(100);
    Camera.setContrast(100);
    cout<<"cameraid:"<<Camera.getId()<<endl;
    cout<<"Image Effect:"<<Camera.getImageEffect()<<endl;
    cout<<"formate"<<Camera.getFormat()<<endl;
    cout<<"height"<<Camera.getWidth()<<endl;
    cout<<"sharpness"<<Camera.getSharpness()<<endl;
    cout<<"Contrast"<<Camera.getContrast()<<endl;
        
    if (!Camera.setStereoMode(1))
    {
        cerr<<"Error opening camera"<<endl;
        return -1;
    }
    //wait a while until camera stabilizes
    cout<<"Sleeping for 3 secs"<<endl;
    usleep(3);
    //capture
    Camera.grab();
    //allocate memory
    unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    //extract the image in rgb format
    Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );//get camera image
    //save
    std::ofstream outFile ( "test.ppm",std::ios::binary );
    outFile<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() <<" 255\n";
    outFile.write ( ( char* ) data, Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    cout<<"Image saved at test.ppm"<<endl;
    //free resrources    
    delete data;
    return 0;
}
int main(int argc, char const *argv[])
{
    camera();
    return 0;
}
