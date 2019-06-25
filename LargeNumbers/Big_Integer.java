import java.util.Scanner;
import java.math.BigInteger;

/**
*	IMPORTANTE:
*	Al hacer operaciones siempre asignar el resultado de la siguiente manera:
*	
*	BigInteger x=BigInteger.valueOf(n);
*	BigInteger dos=BigInteger.valueOf(2)
*	BigInteger doble=x.multiply(dos);
*
*	Operaciones básicas:
*	multiply()
*	subtract()
*	add()
*	divide()
*/

public class Big_Integer {
	
	public static BigInteger array[];
	
	public static BigInteger square(long x) {
		BigInteger cuadrado=BigInteger.valueOf(x*x);
		return cuadrado;
	}
	
	public static void main(String[] args) {
		Scanner cin=new Scanner(System.in);
		int n=cin.nextInt();
		array=new BigInteger[n];
		array[0]=BigInteger.valueOf(0);
		BigInteger dos=BigInteger.valueOf(2);
		for(int i=1;i<n;i++)
			array[i]=array[i-1].multiply(dos);
		System.out.println(dos);
	}
	
}
