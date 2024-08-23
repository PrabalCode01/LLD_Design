

// A shallow copy of an object or array creates a new object or array but does not create copies of nested objects or arrays within it. Instead, the nested structures are referenced from the original object.

var original = {
    name: "Alice",
    details: {
      age: 25,
      city: "New York"
    }
  };
  
  let shallowCopy = { ...original };
  
  // Modify nested object
  shallowCopy.details.age = 30;
  
  console.log(original.details.age); // 30 (affected by change in shallowCopy)

  
//   In this example, shallowCopy contains a reference to the same details object as original. Thus, changes to details in shallowCopy also affect original.


// Deep Copy -> 
// A deep copy creates a new object or array and recursively copies all nested objects or arrays. This means that the new object or array is entirely independent of the original, with no shared references to nested structures.

let original = {
    name: "Alice",
    details: {
      age: 25,
      city: "New York"
    }
  };
  
  // Deep copy using JSON methods (simple approach, limited to JSON-serializable data)
  let deepCopy = JSON.parse(JSON.stringify(original));
  
  // Modify nested object
  deepCopy.details.age = 30;
  
  console.log(original.details.age); // 25 (not affected by change in deepCopy)
  


//   In this example, deepCopy is a completely independent copy of original, including its nested details object. Changes to deepCopy do not affect original.



// Shallow Copy: Copies the top-level properties. Nested objects or arrays are still referenced from the original.
// Deep Copy: Copies the entire structure, including all nested objects or arrays, creating a completely independent copy.