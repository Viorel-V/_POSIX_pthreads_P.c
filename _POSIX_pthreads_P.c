#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

int Writings =0;

void *writer(void *p); 
void *reader(void *t);

pthread_mutex_t mutex_writer;
pthread_mutex_t mutex_rewriter;

int rewriting_Count=0;

void *writer(void *p){                                  // this 'writer' function is the definition of the 
                                                        // first thread th[0] declared in the 'main' function;  

        long int x = 0;
         
    while(1){
       
        pthread_mutex_lock(&mutex_writer); 
        
         x=random();
         if(x<1000)
           x=1000;
         x/=2147.483647; 
                                                         //  Sleep for a random interval between 1 to 1000 milliseconds 
          usleep(x);

        Writings++;                                      // here, we increment the global integer counter 'Writings'
        
        printf("Writer is writing  %d ; \n", Writings);  // here is displayed the content of global counter 'Writins' 
                                                         // after its previous post-incrementation

        pthread_mutex_unlock(&mutex_writer); 
       

    }

}



void *rewriter(void *t){        // this 'reader' function is the definition of the second 
                                // thread th[1] declared in the 'main' function;

    int int_stdin=0;            // this is the variable where is loaded the integer from the keyboard 
    long int y = 0;

    while(1){                   // this while keeps the infinitive cyclicity of this thread
     
        
        pthread_mutex_lock(&mutex_rewriter);     
          
          y=random();
         if(y<1000)
           y=1000;
         y/=2147.483647;  

         usleep(y);    // here is provided the delay/Sleep for a random interval between 1 to 1000 milliseconds 

        scanf("%d", &int_stdin);  // wait here till any integer number is entered from the keyboard, followed by ENTER key. 
                                  // The typed integer is loaded by function 'scanf' in the integer variable 'int_stdin' 
                                  // that is then added to the current content of global "Writings"..

        Writings += int_stdin;    // here, in the global counter 'Writins' is loaded/stored the integer typed from the keyboard. 

        printf("Reader is reading %d ; \n", Writings);   // here is displayed the new content of global variable 
                                                         // 'Writings', as: "Reader is reading .......(the number))" 

        pthread_mutex_unlock(&mutex_rewriter);     
    }

}





int main()

{  

    pthread_t t1, t2;                      //    we declare/create a matrice of two threads, th[0] and th[1];
    int th[2];
   
    pthread_mutex_init(&mutex_writer, NULL);
    pthread_mutex_init(&mutex_rewriter, NULL);

    pthread_create(&t1, NULL, writer, (void*)(&th[0]));
    pthread_create(&t2, NULL, rewriter, (void*)(&th[1]));

    pthread_join(t1, NULL);                  //    these two 'join' functions alternatively block the two threads;   
    pthread_join(t2, NULL);
       

     pthread_mutex_destroy(&mutex_writer); 
     pthread_mutex_destroy(&mutex_rewriter);

}
