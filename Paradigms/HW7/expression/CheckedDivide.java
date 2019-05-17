package expression;

import myExceptions.IllegalOperationException;
import myExceptions.OverflowException;

public class CheckedDivide extends AbstractBinaryOperator {
    public CheckedDivide(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected void check(final int x, final int y) throws IllegalOperationException, OverflowException {
        if (y == 0) {
            throw new IllegalOperationException("Division by zero");
        }
        if (x == Integer.MIN_VALUE && y == -1) {
            throw new OverflowException();
        }
    }

    protected int calculate(final int x, final int y) throws IllegalOperationException, OverflowException {
        check(x, y);
        return x / y;
    }
}
