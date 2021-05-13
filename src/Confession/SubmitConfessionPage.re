open Utils;

requireCSS("src/styles.css");

type state = {
  input: string,
  loading: bool,
  submitted: bool,
  postError: bool,
};

type action =
  | UpdateInput(string)
  | Submit
  | Loading
  | PostErrorOccured(string);

let initialState = {
  input: "",
  submitted: false,
  loading: false,
  postError: false,
};

[@react.component]
let make = _ => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | UpdateInput(newInput) => {...state, input: newInput}
        | Loading => {...state, loading: true}
        | Submit => {...state, loading: false, submitted: true}
        | PostErrorOccured(message) => {
            ...state,
            loading: false,
            postError: true,
          }
        },
      initialState,
    );

  let submitConfession = () => {
    dispatch(Loading);
    let value = state.input;
    let _ =
      ConfessionData.createConfession(value, callback =>
        switch (callback) {
        | None => dispatch(PostErrorOccured("None"))
        | Some(confession) => dispatch(Submit)
        }
      );
    ();
  };

  let renderForm = () =>
    <div>
      <form
        onSubmit={event => {
          ReactEvent.Form.preventDefault(event);
          submitConfession();
          ();
        }}>
        <textarea
          id="submit"
          name="submit"
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
      </form>
    </div>;

  let renderSubmittedMessage = () =>
    <div>
      <a href="/">
        {ReasonReact.string(
           "You have submitted, click this link to view confessions",
         )}
      </a>
    </div>;

  switch (state) {
  | {input: _, submitted: false, loading: false, postError: false} =>
    renderForm()

  | {input: _, loading: true, submitted: false, postError: false} =>
    <SendingMessage />

  | {input: _, submitted: true, loading: false, postError: false} =>
    renderSubmittedMessage()

  | {input: _, submitted: _, loading: _, postError: true} => <ErrorMessage />
  };
};
