package expression;

import myExceptions.OverflowException;

public class CheckedMultiply extends AbstractBinaryOperator {
    public CheckedMultiply(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected void check(final int x, final int y) throws OverflowException {
        if (x > 0 && y > 0 && Integer.MAX_VALUE / x < y) {
            throw new OverflowException();
        }
        if (x > 0 && y < 0 && Integer.MIN_VALUE / x > y) {
            throw new OverflowException();
        }
        if (x < 0 && y > 0 && Integer.MIN_VALUE / y > x) {
            throw new OverflowException();
        }
        if (x < 0 && y < 0 && Integer.MAX_VALUE / x > y) {
            throw new OverflowException();
        }
    }

    protected int calculate(final int x, final int y) throws OverflowException {
        check(x, y);
        return x * y;
    }
}
