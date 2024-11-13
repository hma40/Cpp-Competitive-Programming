import java.util.Scanner;

public class OnesForAll_John {

	public static final int MAXN = 150000;
	
	public static void main(String[] args) {

		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int [] table = new int[n+1];
		
		table[0] = MAXN;
		table[1] = 1;
		for(int i=2; i<=n; i++) {
			table[i] = MAXN;
										// check for a+b=i
			for(int j=1; j<= i/2; j++) {
				if (table[j] + table[i-j] < table[i]) {
					table[i] = table[j] + table[i-j];
				}
			}
										// check for a*b = i
			for(int j=2; j<Math.sqrt(i+1); j++) {
				if (i%j == 0 && table[j] + table[i/j] < table[i]) {
					table[i] = table[j] + table[i/j];
				}
			}
										// check for a@b = i
			String s = i+"";
			for(int j=1; j<s.length(); j++) {
				int n1 = Integer.parseInt(s.substring(0,j));
				int n2 = Integer.parseInt(s.substring(j));
				if (table[n1] + table[n2] < table[i] && s.charAt(j) != '0') {
					table[i] = table[n1] + table[n2];
				}
			}
		}
		System.out.println(table[n]);
	}
}
