import java.util.Scanner;
import java.math.BigInteger;
import java.io.*;
class Main{
	public static void main(String[] args){
		Scanner s = new Scanner(System.in);

		int t = s.nextInt();
		for(int z = 1; z<=t; z++){
			int res = 0;
			int ct = 0;
			String str = s.next();
			int len = str.length();
			while(ct<len)
			{
				int c = Character.getNumericValue(str.charAt(len-ct-1));

				int exp = 
				res+=exp*c;
				ct++;
			}
			// res+=3;
			res%=13;
			if(res == 0)
				res = 13;
			System.out.println("Case #"+z+": "+res);
		}
	}
}
