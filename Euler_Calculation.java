package Proyecto;

import java.math.BigDecimal;
import java.math.RoundingMode;


/**
 * Created by kotoromo on 29/11/16.
 */
public class Euler_Calculation {

    // La clase BigDecimal es un tipo de dato auxiliar que nos permite manejar números enormes.
    // La firma del constructor es: BigDecimal(int number)
    BigDecimal res = new BigDecimal(0);

    //Declaramos el numero a calcular de e
    int limit = 10000000;

    //La palabra reservada synchronized nos permite manejar la contienda del dato que estamos ocupando, en este
    //caso, el atributo res.

    //El método compute se encarga de calculuar el número e
    synchronized void compute(){
        //int i = 0;

        //La definición del número e es la suma desde i=0 hasta n de 1/el factorial de n
        for(int i = 0; i<=limit; i++){

            //Declaración de una clase anónima
            //Debido a que la clase Thread es una clase abstracta, no se puede instanciar directamente.
            //Como sólo ocupamos la declaración del método, es mejor no crear una clase aparte que implemente
            //la clase abstracta Runnable.

            //Por cada iteración de i, se genera un nuevo hilo
            new Thread(){
                //Declaración del método run
                public void run(int i){
                    // res es igual a si mismo más el siguiente número en la serie 1/el factorial de n
                    res = res.add(BigDecimal.ONE.divide(factorial(new BigDecimal(i)), 100, RoundingMode.HALF_UP));
                }
            }.run(i);
        }

        //Imprimimos el resultado
        System.out.println(res.toString());
    }


    //Método que se encarga de calcular un factorial. Retorna un objeto de la clase BigDecimal y toma como
    //parámetro un objeto de la clase BigDecimal.
    public static BigDecimal factorial(BigDecimal n) {
        if (n.equals(BigDecimal.ZERO))
            return BigDecimal.ONE;
        else
            return n.multiply(factorial(n.subtract(BigDecimal.ONE)));
    }

    //Método principal
    public static void main(String args[]){
        new test().compute();
    }
}
