import java.util.*;

 

public class D {

       int limit;

       ArrayList<Integer> primes;

      

       public D(int lim) {

              // TODO Auto-generated constructor stub

              this.limit = lim;

              primes = new ArrayList<Integer>();

              primes.add(2);

             

              for(int i=2;i<=limit;i++) {

                      int flag=1;

                      for(int j=0; j < primes.size(); j++) {

                        if(i%primes.get(j) == 0) flag = 0;

                      }

                      if(flag==1) {
                          primes.add(i);
                          System.out.println(i);
                      }

              }

       }

 

       public static void main(String[] args) {

             D p = new D(Integer.parseInt(args[0]));
             

       }

      

}