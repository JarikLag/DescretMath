package queue;

public abstract class AbstractQueue implements Queue{
    protected int size;

    protected abstract void enqueueImpl(Object obj);

    protected abstract Object elementImpl();

    protected abstract void remove();

    protected abstract void clearImpl();

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

        Object answer = element();
        size--;
        remove();
        return answer;
    }

    public Object[] toArray() {
        Object[] ans = new Object[size];
		for (int i = 0; i < size; i++) {
			ans[i] = dequeue();
			enqueue(ans[i]);
		}
		return ans;
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
