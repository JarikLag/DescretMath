package expression;

public abstract class AbstractBinaryOperator implements TripleExpression {
    private final TripleExpression first;
    private final TripleExpression second;

    protected AbstractBinaryOperator(final TripleExpression first, final TripleExpression second) {
        this.first = first;
        this.second = second;
    }

    protected abstract int calculate(final int x, final int y);

    public int evaluate(final int x, final int y, final int z) {
        return calculate(first.evaluate(x, y, z), second.evaluate(x, y, z));
    }
}
