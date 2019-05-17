package expression;

public abstract class AbstractUnaryOperator implements TripleExpression {
    protected final TripleExpression operand;

    protected AbstractUnaryOperator(final TripleExpression operand) {
        this.operand = operand;
    }

    protected abstract int calculate(final int x);

    public int evaluate(final int x, final int y, final int z) {
        return calculate(operand.evaluate(x, y, z));
    }
}
