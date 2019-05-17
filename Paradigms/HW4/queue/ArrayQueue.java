package queue;

public class ArrayQueue extends AbstractQueue {
    private int head;
    private Object[] array = new Object[4];

    private void ensureCapacity() {
        if (array.length == size) {
			Object[] tmp = new Object[2 * size];
			System.arraycopy(array, head, tmp, 0, array.length - head);
            System.arraycopy(array, 0, tmp, array.length - head, size - array.length + head);
            head = 0;
			array = tmp;
        }
    }

    public void enqueueImpl(Object obj) {
        ensureCapacity();
        array[(head + size) % array.length] = obj;
    }

    public Object elementImpl() {
        return array[head];
    }

    public void remove() {
        head = (head + 1) % array.length;
    }

    public void clearImpl() {
        array = new Object[4];
        head = 0;
    }
}