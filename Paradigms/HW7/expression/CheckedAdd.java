package expression;

import myExceptions.OverflowException;

public class CheckedAdd extends AbstractBinaryOperator {
    public CheckedAdd(final TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    protected void check(final int x, final int y) throws OverflowException {
        if (x > 0 && Integer.MAX_VALUE - x < y) {
            throw new OverflowException();
        }
        if (x < 0 && Integer.MIN_VALUE - x > y) {
            throw new OverflowException();
        }
    }

    protected int calculate(final int x, final int y) throws OverflowException {
        check(x, y);
        return x + y;
    }
}
