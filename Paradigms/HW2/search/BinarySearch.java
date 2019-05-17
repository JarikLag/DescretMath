package search;

public class BinarySearch {
	// Pre: arr != null && for all i=0..arr.length - 2: arr[i] >= arr[i + 1]
    static int iterBinSearch(int[] arr, int x) {
        int l = -1, r = arr.length;
		// l == -1 && r == arr.length
		// Inv: (r == arr.length || (r < arr.length && arr[r] <= x)) && (l == -1 || (0 <= l < arr.length && a[l] > x)) && (r - l >= 1)
        while (r - l > 1) {
			//Pre && Inv
            int m = (l + r) / 2;
			//Pre && Inv && m == (l + r) / 2
            if (arr[m] <= x) {
			//Pre && Inv && m == (l + r) / 2 && arr[m] <= x
                r = m;
			// r' == m == (r + l) / 2 && l' == l
            // l' == l -> (l' == -1 || (0 <= l' < arr.length && arr[l'] > x))
            // Pre && arr[r' == m] <= x && l < m < r -> (r' < arr.length && arr[r'] <= x)
            // r - l > 1 && r' == m && l < m < r -> r' - l' >= 1

            // Pre && Inv
            } else {
				// Pre && Inv && m ==  (r + l) / 2 && arr[m] > x
                l = m;
				// l' == m == (l + r) / 2 && r' = r
                // r' == r -> (r' == arr.length || (r' < arr.length && arr[r'] <= x))
                // Pre && a[l' == m] > x && l < m < r -> (0 <= l' < arr.length && a[l'] > x)
                // r - l > 1 && l' == m && l < m < r -> r' - l' >= 1

                // Pre && Inv
            }
        }
		// !((r - l) > 1) && Inv -> l - r == 1
        // Pre && Inv && l - r == 1
        // 1) arr.length == 0 -> never visited while -> r == 0 && l == -1
        // 2) arr.last > x -> never visited if block in while -> r == arr.length && l = arr.length - 1
        // 3) r < arr.length && Inv -> arr[r] <= x
        // 3a) r == 0
        // 3b) r > 0 && Inv && (l + 1 == r) -> arr[r - 1] > x
        return r;
    }
	// Post: (arr[i]' == arr[i]) && (x' == x) && ((arr.length == 0 && ans == 0) || (arr.last > x && ans == arr.length) 
	// || (ans < arr.length && arr[ans] <= x && (ans == 0 || arr[ans - 1] > x)))

	// Pre: for all arr != null && for all i=0..arr.length - 2: arr[i] >= arr[i + 1] && x' == x && for all i=0..arr.length - 1 : arr'[i] == arr[i]
	// (r == arr.length || (r < arr.length && arr[r] <= x)) && (l == -1 || (0 <= l < arr.length && arr[l] > x)) && (r - l >= 1)
    static int recurBinSearch(int arr[], int x, int l, int r) {
        if (r - l == 1) {
			// Pre && r - l == 1
			// 1) arr.length == 0 -> it is first level of recursion -> r == 0 && l == -1
            // 2) arr.length > 0 && arr.first <= x -> never visited second part of recursion -> r == 0 && l == -1
            // 3) arr.length > 0 && l != -1 -> arr[l] > x
            // 3a) arr.last > x && r == arr.length
            // 3b) r < arr.length && arr[r] <= x
            return r;
        } else {
			// Pre && r > l + 1
			int m = (l + r) / 2;
			// Pre && r > l + 1 && m == (l + r) / 2
			if (arr[m] <= x) {
				// Pre && r - l > 1 && m == (l + r) / 2 && arr[m] <= x
                // l' == l -> (l' == -1 || (0 <= l' < arr.length && arr[l'] > x))
                // r' == m && l' == l -> r' - l' == m - l == (l + r) / 2 - l
                // r - l > 1 && r' == m && l < m < r -> r' - l' >= 1
                // Pre is true for l == l' && r == r'
				return recurBinSearch(arr, x, l, m);
				//Post
			} else {
				// Pre && r - l > 1 && m == (l + r) / 2 && arr[m] <= x
                // l' == m && r' == r -> r' - l' == r' - m == r - (r + l) / 2
                // r' == r -> ((r' == arr.length) || (r' < arr.length && arr[r'] <= x))
                // r - l > 1 && l' == m && l < m < r -> r' - l' >= 1
                // Pre is true for l == l' && r == r'
				return recurBinSearch(arr, x, m, r);
				//Post
			}
		}
    }
	// Post: (arr[i]' == arr[i]) && (x' == x) && ((arr.length == 0 && ans == 0) || (arr.last > x && ans == arr.length) 
	// || (ans < arr.length && arr[ans] <= x && (ans == 0 || arr[ans - 1] > x)))

    public static void main(String[] args) {
		if (args.length == 0) {
			System.out.println("Not enough arguments");
			return;
		}
		try {
			int size = args.length - 1;
			int key = Integer.parseInt(args[0]);
			int[] a = new int[size];
			for (int i = 0; i < size; i++) {
				a[i] = Integer.parseInt(args[i + 1]);
			}
			//System.out.println(iterBinSearch(a, key));
			System.out.println(recurBinSearch(a, key, -1, size));
		} catch (NumberFormatException e) {
			System.out.println("Wrong format of input data");
		}
    }
}
