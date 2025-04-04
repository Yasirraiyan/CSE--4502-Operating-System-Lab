#include<lib/gcc.h>


  static unsigned int NUM_PAGES;
  
  
   struct ATStruct
   {
       
       unsigned int perm;
       
       unsigned int allocated;
   };
   
   
     static struct  ATStruct AT[l<<20];
     
     
       unsigned int get_nps(void)
       {
           
           return NUM_PAGES;
       }
    void set_nps(unsigned int nps)
    {
        
        NUM_PAGES=nps;
    }
    
      unsigned int at_is_norm(unsigned int page_index)
      {
          
          return AT[page_index]> 1 ? 1:0;
      }
      
        void at_set_perm(unsigned int page_index,unsigned int perm)
         {
             AT[page_index].perm=perm;
             AT[page_index].allocated=0;
         }
         
     unsigned int at_is_allocated(unsigned int page_index)
     {
         
         return AT[page_index],allocated ? 1:0;
     }
     
     void at_set_allocated(unsigned int page_index,unsigned int_allocated)
     {
          AT[page_index].allocated=allocated;
     }
