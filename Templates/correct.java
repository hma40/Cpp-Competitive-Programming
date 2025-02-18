import java.util.*;
import java.io.*;
public class correct {
    public static void main(String[] args) throws IOException {
        BufferedReader rr = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        StringTokenizer st = new StringTokenizer(rr.readLine());
        int T = Integer.parseInt(st.nextToken());
        while(T-- > 0) {
            st = new StringTokenizer(rr.readLine());
            int n = Integer.parseInt(st.nextToken());
            int k = Integer.parseInt(st.nextToken()) * 2;
            int l = Integer.parseInt(st.nextToken()) * 2;
            st = new StringTokenizer(rr.readLine());
            int[] arr = new int[n];
            for(int i = 0; i < n; i++) {
                arr[i] = Integer.parseInt(st.nextToken()) * 2;
            }
            if(n == 1) {
                pw.println(arr[0] + Math.max(0, l - k));
            } else {
                int time = arr[0];
                arr[0] = 0;
                for(int i = 1; i < n; i++) {
                    if(arr[i] - arr[i - 1] > k) {
                        arr[i] -= Math.min(time, arr[i] - arr[i - 1] - k);
                    } else {
                        arr[i] += Math.min(time, arr[i - 1] + k - arr[i]);
                    }
                }
                //System.out.println(Arrays.toString(arr));
                int crow = 0;
                int index = 0;
                while(crow - arr[index] <= k && crow - arr[index] >= 0) {
                    crow = arr[index] + k;
                    index++;
                    if(index == n) {break;}
                }
                //System.out.println(crow + ", " + index);
                int free = 0;
                while(crow < l) {
                    if(index == n) {
                        time += l - crow;
                        crow = l;
                    } else {
                        int next = (arr[index] - crow)/2;
                        free += next;
                        if(crow + next >= l) {
                            time += l - crow;
                            crow = l;
                        } else {
                            time += next;
                            free += next;
                            crow += next;
                            arr[index] -= next;
                            while(crow - arr[index] <= k && crow - arr[index] >= 0) {
                                crow = arr[index] + k;
                                index++;
                                if(index == n) {break;}
                                if(arr[index] - arr[index - 1] > k) {
                                    arr[index] -= Math.min(free, arr[index] - arr[index - 1] - k);
                                } else {
                                    arr[index] += Math.min(free, arr[index - 1] + k - arr[index]);
                                }
                            }
                        }
                    }
                }
                pw.println(time);
            }
        }

        pw.close();
    }
}
