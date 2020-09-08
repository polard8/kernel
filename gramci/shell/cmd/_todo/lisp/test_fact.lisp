(define factorial
  (lambda (x)
    (cond ((eq x 1) 1)
          ('t (* x (factorial (- x 1)))))))
(factorial 10)
