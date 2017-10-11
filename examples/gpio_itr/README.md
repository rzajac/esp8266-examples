## Interrupt example.

Example shows how to:

- attach Interrupt Service Routine (ISR) to GPIO pin, 
- handle interrupts on that pin.

## Example console output.

Every time level on GPIO2 pin changes from LOW to HIGH the ISR is called which 
increments edge_counter.

```text
Edge counter: 1
Edge counter: 2
Edge counter: 3
Edge counter: 4
Edge counter: 5
Edge counter: 6
Edge counter: 7
Edge counter: 8
Edge counter: 9
```