/**
 * Read FAQs section on the left for more information on how to use the editor
**/


const virtualNode = {
    type: "div",
    props: {
      class: "heading-container",
      children: {
        0: "This is",
        1: {
          type: "h1",
          props: {
            key: "10",
            id: "heading",
            children: "devtools.tech",
          },
        },
        2: {
          type: "h2",
          props: {
            id: "heading",
            children: "is Awesome!!",
          },
        },
        3: {
          type: "input",
          props: {
            type: "text",
            value: "Devtools Tech",
          },
        },
        4: {
          type: "button",
          props: {
            children: "Click",
          },
        },
        5: 0,
        6: {
          props: {
            children: {
              0: {
                type: "div",
                props: {
                  children: "React",
                },
              },
              1: {
                type: "div",
                props: {
                  children: "Fragment",
                },
              },
            },
          },
        },
        7: "",
      },
    },
  };
  
  const domNode = document.getElementById('root');
  
  renderToDOM(virtualNode, domNode);

  
// visualizing the output 
// <div class="heading-container"> 
//This is
// <h1 id="heading" key="10">devtools.tech</h1>
// <h2 id="heading">is Awesome!!</h2>
// <input type="text" value="Devtools Tech">
// <button>Click</button>
// <div>React</div>
// <div>Fragment</div>
// <div>Devtools Tech</div>
// </div>
// DO NOT CHANGE FUNCTION NAME


function render(node){
    if(node === null) return null; 

    //text node
    if(node !== "object"){
        return document.createTextNode(node.toString()); 
    }

    // fragment node
    if(!node.type && node.props && node.props.children){
        const fragment = document.createDocumentFragment(); 
        const children = node.props.children || {}; 

        Object.keys(children).forEach(key => {
            const childNode = render(children[key]); 

            if(childNode){
                fragment.appendChild(childNode); 
            }
        })

        return fragment; 
    }

    //html elements
    const element = document.createElement(node.type); 

    if(node.props){
        Object.entries(node.props).forEach(([key, value]) => {
            if(key === "children" && typeof value === "object"){
                const childNode = render(child); 

                if(childNode){
                    element.appendChild(childNode); 
                }
            }
            else if(key === "class"){
                element.className = value;
            }
            else if(key === "id"){
                element.id = value; 
            }
            else if(key === "key"){
                element.setAttribute(key, value); 
            }
        })
    }

    if(node.props.children){
        
    }


}
function renderToDOM(virtualNode, domNode) {
    // write your solution below
    // do not return anything, you'd just have to append into the domNode 
    // yes.... 


    const renderedContent = render(virtualNode); 

    if(renderedContent){
        domNode.appendChild(renderedContent);
    }
    
  }
  
  // 0: Hide test cases UI
  // 1: Show test cases UI
  window.__SHOW_ELEMENTS__ = 0;
  