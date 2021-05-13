open Belt;

type state = {
  confession: option(ConfessionData.confession),
  input: string,
  submitted: bool,
  fetchError: bool,
  postError: bool,
};

type action =
  | Loaded(ConfessionData.confession)
  | UpdateInput(string)
  | Submit
  | FetchErrorOccured(string)
  | PostErrorOccured(string);

let initialState = {
  confession: None,
  input: "",
  submitted: false,
  fetchError: false,
  postError: false,
};

[@react.component]
let make = (~id) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Loaded(data) => {...state, input: "", confession: Some(data)}
        | UpdateInput(newInput) => {...state, input: newInput}
        | Submit => {...state, submitted: true}
        | FetchErrorOccured(message) => {...state, fetchError: true}
        | PostErrorOccured(message) => {...state, postError: true}
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

  // let testFunction = () => {
  //   Js.log("my test function was called");
  // };

  <div>
    {switch (state.confession) {
     | Some(confession) =>
       <div>
         <ConfessionListItem key={confession.id} index=1 confession />
         <form
           className="ConfessionListItem_commentRow"
           onSubmit={event => {
             ReactEvent.Form.preventDefault(event);

             let _ =
               ConfessionData.createComment(
                 confession.id, state.input, callback =>
                 switch (callback) {
                 | None => dispatch(PostErrorOccured("None"))
                 | Some(confession) => dispatch(Loaded(confession))
                 }
               );
             ();
           }}>
           //let _ = ConfessionData.createComment(confession.id, state.input);
           //  let newComment: ConfessionData.confessionComment = {
           //    message: state.input,
           //    id: state.input,
           //    ts: 123,
           //  };
           //  let newCommentArray = [|newComment|];
           //  let newComments: ConfessionData.comments = {
           //    commentsArray:
           //      Array.concat(
           //        confession.comments.commentsArray,
           //        newCommentArray,
           //      ),
           //  };
           //  let newData: ConfessionData.confession = {
           //    message: confession.message,
           //    id: confession.id,
           //    ts: confession.ts,
           //    comments: newComments,
           //  };
           //  dispatch(Loaded(newData));

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
       </div>
     | None => React.string("loading")
     }}
  </div>;
  //need to change ui based on state up first i need to make this form better
  //no to refactor the components then add the loading state to this component
};
