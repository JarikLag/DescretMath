package expression;

import myExceptions.IllegalOperationException;

public class CheckedLog extends AbstractBinaryOperator {
    public CheckedLog(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected void check(final int x, final int y) throws IllegalOperationException {
        if (x <= 0) {
            throw new IllegalOperationException("Log form negative");
        }
        if (y <= 1) {
            throw new IllegalOperationException("Incorrect log base");
        }
    }

    protected int calculate(final int x, final int y) throws IllegalOperationException {
        check(x, y);
		int xCopy = x, ans = 0;
        while (xCopy >= y) {
			xCopy /= y;
			ans++;
		}
		return ans;
    }
}
