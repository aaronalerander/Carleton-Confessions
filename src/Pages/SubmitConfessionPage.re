open Utils;

requireCSS("src/styles.css");

type state = {
  input: string,
  submitting: bool,
  successfulSubmit: bool,
  postError: bool,
};

type action =
  | UpdateInput(string)
  | Submitting
  | SuccessfulSubmit
  | PostErrorOccured;

let initialState = {
  input: "",
  successfulSubmit: false,
  submitting: false,
  postError: false,
};

[@react.component]
let make = _ => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | UpdateInput(newInput) => {...state, input: newInput}
        | Submitting => {...state, submitting: true}
        | SuccessfulSubmit => {
            ...state,
            submitting: false,
            successfulSubmit: true,
          }
        | PostErrorOccured => {...state, submitting: false, postError: true}
        },
      initialState,
    );

  let submitConfession = () => {
    dispatch(Submitting);
    let value = state.input;
    let _ =
      Api.createConfession(value, callback =>
        switch (callback) {
        | None => dispatch(PostErrorOccured)
        | Some(confession) =>
          dispatch(SuccessfulSubmit);
          Js.log(confession);
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
          className="recentConfessionsListItemTextArea"
          value={state.input}
          onChange={event => {
            let value = ReactEvent.Form.target(event)##value;
            dispatch(UpdateInput(value));
          }}
        />
        <button type_="submit" className="recentConfessionsListItemButton">
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
  | {input: _, successfulSubmit: false, submitting: false, postError: false} =>
    renderForm()

  | {submitting: true} => <SendingMessage />

  | {successfulSubmit: true} => renderSubmittedMessage()

  | {postError: true} => <ErrorMessage />
  };
};
