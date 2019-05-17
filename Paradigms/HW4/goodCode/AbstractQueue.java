package queue;

public abstract class AbstractQueue implements Queue{
    protected int size;

    protected abstract void enqueueImpl(Object obj);

    protected abstract Object elementImpl();

    protected abstract void remove();

    protected abstract void clearImpl();

    protected abstract Object[] toArrayImpl();

    public void enqueue(Object obj) {
        assert obj != null;

        enqueueImpl(obj);
        size++;
    }

    public Object element() {
        assert size > 0;

        return elementImpl();
    }

    public Object dequeue() {
        assert size > 0;

        Object answer = element();
        size--;
        remove();
        return answer;
    }

    public Object[] toArray() {
        return toArrayImpl();
    }

    public void clear() {
        clearImpl();
        size = 0;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }
}
