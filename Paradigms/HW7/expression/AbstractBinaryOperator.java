package expression;

import myExceptions.EvaluatingException;

public abstract class AbstractBinaryOperator implements TripleExpression {
    private final TripleExpression first;
    private final TripleExpression second;

    protected AbstractBinaryOperator(final TripleExpression first, final TripleExpression second) {
        this.first = first;
        this.second = second;
    }

    protected abstract void check(final int x, final int y) throws EvaluatingException;

    protected abstract int calculate(final int x, final int y) throws EvaluatingException;

    public int evaluate(final int x, final int y, final int z) throws EvaluatingException {
        return calculate(first.evaluate(x, y, z), second.evaluate(x, y, z));
    }
}
