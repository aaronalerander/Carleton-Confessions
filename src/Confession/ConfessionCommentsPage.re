open Belt;

//this file should have a better name like confessionPage

type state = {
  confession: option(ConfessionData.confession),
  input: string,
  loading: bool,
  submitting: bool,
  fetchError: bool,
  postError: bool,
};

type action =
  | Loaded(ConfessionData.confession)
  | UpdateInput(string)
  | Loading
  | Submitting
  | FetchErrorOccured(string)
  | PostErrorOccured(string);

let initialState = {
  confession: None,
  input: "",
  loading: true,
  submitting: false,
  fetchError: false,
  postError: false,
};

[@react.component]
let make = (~id) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Loaded(data) => {
            ...state,
            input: "",
            loading: false,
            submitting: false,
            confession: Some(data),
          }
        | UpdateInput(newInput) => {...state, input: newInput}
        | Loading => {...state, loading: true}
        | Submitting => {...state, submitting: true}
        | FetchErrorOccured(message) => {
            ...state,
            loading: false,
            fetchError: true,
          }
        | PostErrorOccured(message) => {
            ...state,
            postError: true,
            submitting: false,
          }
        },
      initialState,
    );

  React.useEffect0(() => {
    let callback = result => {
      switch (result) {
      | None => dispatch(FetchErrorOccured("None"))
      | Some(confession) => dispatch(Loaded(confession))
      };
    };
    ConfessionData.fetchConfessionWithComments(id, callback);
    None;
  });

  let submitComment = confessionId => {
    dispatch(Submitting);
    let _ =
      ConfessionData.createComment(confessionId, state.input, callback =>
        switch (callback) {
        | None => dispatch(PostErrorOccured("None"))
        | Some(confession) => dispatch(Loaded(confession))
        }
      );
    ();
  };

  let renderConfession = confession =>
    <div>
      <ConfessionCommentsPageListItem key={confession.id} confession />
    </div>;

  let renderForm = confessionId =>
    <div>
      <form
        className="ConfessionListItem_commentRow"
        onSubmit={event => {
          ReactEvent.Form.preventDefault(event);
          submitComment(confessionId);
          ();
        }}>
        <textarea
          id="search"
          name="search "
          value={state.input}
          onChange={event => {
            let value = ReactEvent.Form.target(event)##value;
            dispatch(UpdateInput(value));
          }}
        />
        <button type_="submit"> {ReasonReact.string("Comment")} </button>
      </form>
    </div>;

  switch (state) {
  | {loading: true} => <LoadingMessage />

  | {fetchError: true} => <ErrorMessage />

  | {postError: true} =>
    <div>
      {switch (state.confession) {
       | Some(confession) =>
         <div>
           {renderConfession(confession)}
           <ErrorMessage additionalInfo="Error sending comment." />
         </div>
       }}
    </div>

  | {submitting: true} =>
    <div>
      {switch (state.confession) {
       | Some(confession) =>
         <div> {renderConfession(confession)} <SendingMessage /> </div>
       }}
    </div>

  | {loading: false, submitting: false, fetchError: false, postError: false} =>
    <div>
      {switch (state.confession) {
       | Some(confession) =>
         <div>
           {renderConfession(confession)}
           {renderForm(confession.id)}
         </div> //no idea why I cant extract it from the function renderForm??
       }}
    </div>
  };
};
