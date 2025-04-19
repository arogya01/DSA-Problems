// need to visualize this leading and trailing sort of.
// trailing is by default true. 
// and then leading will trigger it for first time. 
function debounce(fn, delay, options = { leading: false, trailing: true }) {
    let timeoutId;
    let lastCallTime = 0; // so, we're adding in the lastCallTime, 
    
    return function(...args) {
        const context = this;
        const now = Date.now(); 
        const isInvoking = options.leading && !timeoutId; // options.leading is true, and timeoutId is true, meaning this thing is getting executed for the first hecking time. 
        clearTimeout(timeoutId);
        
        // Handle leading edge execution
        if (isInvoking) {
            lastCallTime = now;
            fn.apply(context, args);
        }
        
        // Setup trailing edge execution
        if (options.trailing) {
            timeoutId = setTimeout(() => {
                // Only execute if we haven't recently executed via leading option
                const timeSinceLastCall = Date.now() - lastCallTime;
                if (!options.leading || timeSinceLastCall >= delay) {
                    fn.apply(context, args);
                    lastCallTime = Date.now();
                }
                timeoutId = null;
            }, delay);
        }
    };
}

// Example with trailing edge only (default behavior)
const trailingDebouncedFn = debounce((message) => {
    console.log(`${message} here (trailing)`);
}, 300);

// Example with leading edge only
const leadingDebouncedFn = debounce((message) => {
    console.log(`${message} here (leading)`);
}, 300, { leading: true, trailing: false });

// Example with both leading and trailing edge
const bothDebouncedFn = debounce((message) => {
    console.log(`${message} here (both)`);
}, 300, { leading: true, trailing: true });

console.log("--- Trailing edge example (default) ---");
trailingDebouncedFn("hello world");
trailingDebouncedFn("hello world");
trailingDebouncedFn("chi world");

// Wait for trailing edge debounce to complete
setTimeout(() => {
    console.log("\n--- Leading edge example ---");
    leadingDebouncedFn("hello world");
    leadingDebouncedFn("hello world");
    leadingDebouncedFn("chi world");
    
    // Wait for leading edge debounce to reset
    setTimeout(() => {
        console.log("\n--- Both edges example ---");
        bothDebouncedFn("hello world");
        bothDebouncedFn("hello world");
        bothDebouncedFn("chi world");
    }, 400);
}, 400);