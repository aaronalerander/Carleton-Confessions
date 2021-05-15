
type state = {
  confession: option(ConfessionData.confession),
  input: string,
  loadingConfession: bool,
  submittingComment: bool,
  fetchError: bool,
  postError: bool,
};

type action =
  | Load(ConfessionData.confession)
  | UpdateInput(string)
  | LoadingConfession
  | SubmittingComment
  | FetchErrorOccured
  | PostErrorOccured;

let initialState = {
  confession: None,
  input: "",
  loadingConfession: true,
  submittingComment: false,
  fetchError: false,
  postError: false,
};

[@react.component]
let make = (~id) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Load(data) => {
            ...state,
            input: "",
            loadingConfession: false,
            submittingComment: false,
            confession: Some(data),
          }
        | UpdateInput(newInput) => {...state, input: newInput}
        | LoadingConfession => {...state, loadingConfession: true}
        | SubmittingComment => {...state, submittingComment: true}
        | FetchErrorOccured => {
            ...state,
            loadingConfession: false,
            fetchError: true,
          }
        | PostErrorOccured => {
            ...state,
            postError: true,
            submittingComment: false,
          }
        },
      initialState,
    );

  React.useEffect0(() => {
    let callback = result => {
      switch (result) {
      | None => dispatch(FetchErrorOccured)
      | Some(confession) => dispatch(Load(confession))
      };
    };
    Api.fetchConfessionWithComments(id, callback);
    None;
  });

  let submitComment = confessionId => {
    dispatch(SubmittingComment);
    let _ =
      Api.createComment(confessionId, state.input, callback =>
        switch (callback) {
        | None => dispatch(PostErrorOccured)
        | Some(confession) => dispatch(Load(confession))
        }
      );
    ();
  };

  let renderConfession = confession =>
    <div> <ConfessionPageData key={confession.id} confession /> </div>;

  let renderCommentForm = confessionId =>
    <div>
      <form
        className="recentConfessionsListItemCommentRow"
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
  | {loadingConfession: true} => <LoadingMessage />

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

  | {submittingComment: true} =>
    <div>
      {switch (state.confession) {
       | Some(confession) =>
         <div> {renderConfession(confession)} <SendingMessage /> </div>
       }}
    </div>

  | {
      loadingConfession: false,
      submittingComment: false,
      fetchError: false,
      postError: false,
    } =>
    <div>
      {switch (state.confession) {
       | Some(confession) =>
         <div>
           {renderConfession(confession)}
           {renderCommentForm(confession.id)}
         </div>
       }}
    </div>
  };
};
