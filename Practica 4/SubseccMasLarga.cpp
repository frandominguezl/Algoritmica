#include<iostream>
#include<string.h>
using namespace std;


char b[100][100];
int c[100][100];


void SubSecMasLarga(char X[], char Y[]){
    int m,n,i,j;
    m=strlen(X)-1;
    n=strlen(Y)-1;
    //Inicializamos la primera fila a 0
    for(i=1; i<=m; i++)
         c[i][0]=0;
    //Inicializamos la primera columna 0
    for(j=0; j<=n; j++)
        c[0][j]=0;


    for(i=1; i<=m; i++){
      for(j=1; j<=n; j++){
        if (X[i]==Y[j]){
            c[i][j]=c[i-1][j-1]+1;
             b[i][j]='/';
        }
        else{
            if (c[i-1][j]>=c[i][j-1]){
                 c[i][j]=c[i-1][j];
                 b[i][j]='|'; 
            }
            else{
                 c[i][j]=c[i][j-1];
                 b[i][j]='-'; 
            }
       }
     } 
   }
}
void llena(char M[]){

    int i;
    char a;
    a=getchar();
    M[1]=a;// Apartir de aqui se empezara a llenar Los Vectores
    i=2;
    while(a!=10){
       a=getchar();
       M[i]=a;
       i++;
    } 

   M[i-1]='\0'; 

}
void imprimir_SubSec(char X[], int i, int j) // Imprime cada Ocurrencia del Vector B en A
{
    if (i==0 || j==0)
       return ;

    if (b[i][j]=='/'){
        imprimir_SubSec(X,i-1,j-1);
        cout<<X[i];
    }

    else{
        if (b[i][j]=='|')
                imprimir_SubSec(X,i-1,j);
            else // "-"
                imprimir_SubSec(X,i,j-1);
    }
}
int main(){   
    char A[100],B[100];
    int tamA,tamB;
   
    cout<<"Introduce la cadena A: ";
    llena(A);
    fflush(stdin);
    cout<<"Introduce la cadena B: ";
    llena(B);
    fflush(stdin);
    tamA=strlen(A);
    tamB=strlen(B);
    SubSecMasLarga(A,B);
    cout<<"\n\n";
    cout<<"\tTABLA DINAMICA";
    cout<<"\n\n";
    for( int i=0; i<=tamA-1; i++)
    {
        cout<<"\t";
        for( int j=0; j<=tamB; j++)
            if( j+1==tamB+1)
                cout<<endl;

            else
                cout<<" "<<c[i][j];
    } 
    cout<<"\n\n";
    cout<<"La subsecuencia común más larga es:";
    cout<<" {";
    imprimir_SubSec(A,tamA-1,tamB-1);
    cout<<"} de longitud "<<c[tamA-1][tamB-1]<<endl;
}
