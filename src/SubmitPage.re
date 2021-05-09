open Utils;

requireCSS("src/ConfessionListItem.css");

type state = {
  input: string,
  submitted: bool,
};

type action =
  | UpdateInput(string)
  | Submit;

[@react.component]
let make = _ => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | UpdateInput(newInput) => {...state, input: newInput}
        | Submit => {...state, submitted: true}
        },
      {input: "", submitted: false},
    );

  <>
    <div>
      {state.submitted
         ? <a href="/">
             {ReasonReact.string(
                "You have submitted, click this link to view confessions",
              )}
           </a>
         : <form
             onSubmit={event => {
               ReactEvent.Form.preventDefault(event);
               let value = state.input;
               let _ = ConfessionData.createConfession(value);
               dispatch(Submit);
               ();
             }}>
             <textarea
               id="submit"
               name="submit "
               placeholder="Enter your confession here..."
               className="ConfessionListItem_textArea"
               value={state.input}
               onChange={event => {
                 let value = ReactEvent.Form.target(event)##value;
                 dispatch(UpdateInput(value));
               }}
             />
             <button type_="submit" className="ConfessionListItem_button">
               {ReasonReact.string("Submit")}
             </button>
           </form>}
    </div>
  </>;
};
