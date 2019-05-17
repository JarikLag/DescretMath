package expression;

public class Count extends AbstractUnaryOperator {
    public Count(final TripleExpression operand) {
        super(operand);
    }

    protected int calculate(final int operand) {
        int count = 0;
		int copy = operand;
        while (copy != 0) {
            count++;
            copy &= (copy - 1);
        }
        return count;
    }
}