package expression;

import myExceptions.OverflowException;

public class CheckedNegate extends AbstractUnaryOperator {

    public CheckedNegate(final TripleExpression operand) {
        super(operand);
    }

    protected void check(final int x) throws OverflowException {
        if (x == Integer.MIN_VALUE) {
            throw new OverflowException();
        }
    }

    protected int calculate(final int x) throws OverflowException {
        check(x);
        return -x;
    }
}
