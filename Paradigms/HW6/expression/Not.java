package expression;

public class Not extends AbstractUnaryOperator {
    public Not(final TripleExpression operand) {
        super(operand);
    }

    protected int calculate(final int operand) {
        return ~operand;
    }
}
