package queue;
public class Main {
    public static void main(String[] args) {
        for (int i = 0; i < 10; i++) {
            ArrayQueue.enqueue(i);
        }
        for (int i = 0; i < 10; i++) {
            System.out.println(ArrayQueueModule.dequeue());
        }
    }
}
