import java.util.Scanner;
import java.math.BigInteger;
import java.io.*;
class Main{
	public static BigInteger f;
	public static BigInteger getNeededFuel(int mid)
	{
		BigInteger m = BigInteger.valueOf(mid);
		BigInteger res = m.multiply(m.add(BigInteger.valueOf(1)));
		res = res.multiply(m.multiply(BigInteger.valueOf(2)).add(BigInteger.valueOf(1)));
		res = res.divide(BigInteger.valueOf(6));
		return res;
	}
	public static int find(int l, int r)
	{
		int mid = (l+r)/2;
		BigInteger needed = getNeededFuel(mid);
		if(l>=r)
			return (-1)*mid;
		if(needed.compareTo(f) == 0)
			return mid;
		if(needed.compareTo(f)<0)
			return find(mid+1, r);
		else
			return find(l,mid-1);
	}
	public static void main(String[] args){
		Scanner s = new Scanner(System.in);
		int t = s.nextInt();
		for(int z = 1; z<=t; z++){
			f = s.nextBigInteger();
			int res = find(0, 1000000000);
			if(res<1)
			{
				res*=-1;
				if(getNeededFuel(res).compareTo(f)>0)
					res--;
			}
			res+=2;
			System.out.println("Case #"+z+": "+res);
		}
	}
}
