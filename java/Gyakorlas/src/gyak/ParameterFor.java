package gyak;

import java.lang.annotation.*;

import java.lang.annotation.Repeatable;
import java.lang.annotation.Retention;
import java.lang.annotation.Target;



@Repeatable(ParametersFor.class)
@Target({ElementType.METHOD})
@Retention(RetentionPolicy.RUNTIME)
public @interface ParameterFor {
	String s() default "";
	int[] value() default {};
}
