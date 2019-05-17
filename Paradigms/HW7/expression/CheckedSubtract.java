package expression;

import myExceptions.OverflowException;

public class CheckedSubtract extends AbstractBinaryOperator {
    public CheckedSubtract(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected void check(final int x, final int y) throws OverflowException {
        if (x >= 0 && y < 0 && x - Integer.MAX_VALUE > y) {
            throw new OverflowException();
        }
        if (x <= 0 && y > 0 && Integer.MIN_VALUE - x > -y) {
            throw new OverflowException();
        }
    }

    protected int calculate(final int x, final int y) throws OverflowException {
        check(x, y);
        return x - y;
    }
}
