package queue;

public class LinkedQueue extends AbstractQueue {
    private Node head = new Node();
    private Node tail = head;

    protected void enqueueImpl(Object obj) {
        tail.next = new Node(obj);
        tail = tail.next;
    }

    protected Object elementImpl() {
        return head.next.value;
    }

    protected void remove() {
        head = head.next;
    }

    protected void clearImpl() {
        head = new Node();
        tail = head;
    }

    protected Object[] toArrayImpl() {
        Object[] answer = new Object[size];
        Node now = head.next;
        int ind = 0;
        while (now != null) {
            answer[ind] = now.value;
            ind++;
            now = now.next;
        }
        return answer;
    }

    private class Node {
        private Node next;
        private Object value;

        public Node() {
        }

        public Node(Object value) {
            assert value != null;

            this.value = value;
        }
    }
}
