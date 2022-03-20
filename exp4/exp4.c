#include<stdio.h>
#include<stdlib.h>
#include<gd.h>
#include<omp.h>

int main(int argc,char** argv)
{
int w,h,tid,tmp,red,green,blue,x,y,color,n_threads=4;
 w=h=tid=tmp=red=green=blue=color=x=y=0;
double st,end;
char *iname=NULL,*oname=NULL;
FILE *fp=NULL;
gdImagePtr img;
if(argc!=3)
{
	printf("error! format: obj input.png output.png\n");
	exit(0);
}
else
{
	iname = argv[1];
	oname = argv[2];
}
if((fp=fopen(iname,"r"))==NULL)
{
	printf("error! in open file %s",iname);
	exit(0);
}

else
{img = gdImageCreateFromPng(fp);
	w=gdImageSX(img);
	h=gdImageSY(img);
}

omp_set_num_threads(n_threads);
st = omp_get_wtime();
#pragma omp parallel for private(y,tmp,red,green,blue) schedule(guided,50) // schedule(static,50) //schedule(dynamic,50)
for(x=0;x<w;x++)
for(y=0;y<h;y++)
{
	tid=omp_get_thread_num();
	color=gdImageGetPixel(img,x,y);
	red = gdImageRed(img,color);
	green = gdImageGreen(img,color);
	blue = gdImageBlue(img,color);
	tmp = (red+green+blue)/3;
	/*if(tid==0){
	//color=gdImageColorAllocate(img,tmp,tmp,tmp);
	color=gdImageColorAllocate(img,red,0,0);
	gdImageSetPixel(img,x,y,color);
	}*/
	
	/*if(tid==1)	 
	  {color=gdImageColorAllocate(img,0,green,0);
	gdImageSetPixel(img,x,y,color);
	}*/
	

	/*if(tid==2)	 
	  {color=gdImageColorAllocate(img,0,0,blue);
	gdImageSetPixel(img,x,y,color);
	}
	*/

	if(tid==3)	 
	  {color=gdImageColorAllocate(img,0,0,0);
	gdImageSetPixel(img,x,y,color);
	}

}


if((fp=fopen(oname,"w"))==NULL)
{
	printf("error! in open file %s",oname);
	exit(0);
}

else
{gdImagePng(img,fp);
 fclose(fp);
}
end = omp_get_wtime();
printf("time = %lf \n",end-st);
gdImageDestroy(img);


	return 0;
}
