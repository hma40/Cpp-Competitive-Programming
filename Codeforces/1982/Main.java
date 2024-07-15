import java.io.*;
import java.util.*;
public class Main {
    static long MAX_LEN = (long)1e18+50;
    static final String ENDL = "\n";
    public static void main(String[] args) throws Exception {
        InputOutput io = new InputOutput();
	for(int t = io.nextInt(); t > 0; t--) {
	    int n = io.nextInt();
	    int[] val = io.nextIntArr(n);
	}
    }
    static class BinaryTrie {
        Node root = new Node(null);
        void insert(int index, int number) {
            Node cur = root;
            for(int i = 30; i >= 0; i--) {
                if((number&(1<<i))==0) {
		    if(cur.left==null) {
                        cur.left = new Node(cur);
                    }
                    cur=cur.left;
		} else {
                    if(cur.right==null) {
                        cur.right = new Node(cur);
                    }
                    cur = cur.right;
		}
	    }
            while(cur!=root) {
                cur.index=index;
                cur=cur.parent;
            }
	}
        int find(int xor, int tolerance) {
            int ans = -1;
	    Node cur = root;
            for(int i = 30; i >= 0; i--) {
		if((tolerance&(1<<i))!=0) {
		    if((xor&(1<<i))!=0) {
			if(cur.right!=null) ans = Math.max(ans, cur.right.index);
			if(cur.left==null) return ans;
			cur=cur.left;
		    } else {
			if(cur.left!=null) ans = Math.max(ans, cur.left.index);
		    	if(cur.right==null) return ans;
			cur=cur.right;	    
		    }   	
		} else {
		    if((xor&(1<<i))!=0) {
			if(cur.right==null) return ans;
			cur=cur.right;
		    } else {
			if(cur.left==null) return ans;
			cur=cur.left;
		    }
		}	
            }
	    ans = Math.max(ans, cur.index);
	    return ans;		
        }
    }
    static class Node {
        Node parent;
		Node left, right;
		int index;
        Node(Node parent) {
            this.parent=parent;
        }
    }
    static class InputOutput {
        InputStream stream;
        byte[] buf = new byte[1<<16];
        int curChar;
        int numChars;
        PrintWriter pw;
        StringBuilder ans = new StringBuilder();
        public InputOutput() throws Exception {
            pw = new PrintWriter(System.out);
            stream = System.in;
        }
        public InputOutput(String name) throws Exception {
            pw = new PrintWriter(new FileWriter(name+".out"));
            stream = new FileInputStream(name+".in");
        }
        public int[] nextIntArr(int size) {
            int[] ret = new int[size];
            for(int i = 0; i < size; i++) ret[i]=nextInt();
            return ret;
        }
        public long[] nextLongArr(int size) {
            long[] ret = new long[size];
            for(int i = 0; i < size; i++) ret[i]=nextInt();
            return ret;
        }
        private int nextByte() {
            if (numChars == -1) { throw new InputMismatchException(); }
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) { throw new InputMismatchException(); }
                if (numChars == -1) {
                    return -1;  // end of file
                }
            }
            return buf[curChar++];
        }
        public String next() {
            int c;
            do { c = nextByte(); } while (c <= ' ');

            StringBuilder res = new StringBuilder();
            do {
                res.appendCodePoint(c);
                c = nextByte();
            } while (c > ' ');
            return res.toString();
        }
        public int nextInt() {  // nextLong() would be implemented similarly
            int c;
            do { c = nextByte(); } while (c <= ' ');

            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = nextByte();
            }

            int res = 0;
            do {
                if (c < '0' || c > '9') { throw new InputMismatchException(); }
                res = 10 * res + c - '0';
                c = nextByte();
            } while (c > ' ');
            return res * sgn;
        }
        public long nextLong() {  // nextLong() would be implemented similarly
            int c;
            do { c = nextByte(); } while (c <= ' ');

            long sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = nextByte();
            }

            long res = 0;
            do {
                if (c < '0' || c > '9') { throw new InputMismatchException(); }
                res = 10 * res + c - '0';
                c = nextByte();
            } while (c > ' ');
            return res * sgn;
        }
        public double nextDouble() { return Double.parseDouble(next()); }
        public void append(int i) {
            ans.append(i + "\n");
        }
        public void append(long i) {
            ans.append(i + "\n");
        }
        public void append(String s) {
            ans.append(s + "\n");
        }
        public void printAns() {
            pw.print(ans);
            pw.close();
        }
    }
}
