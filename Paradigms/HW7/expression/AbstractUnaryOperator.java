package expression;

import myExceptions.EvaluatingException;

public abstract class AbstractUnaryOperator implements TripleExpression {
    private final TripleExpression operand;

    protected AbstractUnaryOperator(final TripleExpression operand) {
        this.operand = operand;
    }

    protected abstract void check(final int x) throws EvaluatingException;

    protected abstract int calculate(final int x) throws EvaluatingException;

    public int evaluate(final int x, final int y, final int z) throws EvaluatingException {
        return calculate(operand.evaluate(x, y, z));
    }
}
