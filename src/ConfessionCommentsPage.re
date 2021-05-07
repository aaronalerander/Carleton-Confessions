open Belt;
//open Utils;

type state = {
  confession: option(ConfessionData.confession),
  input: string,
  submitted: bool,
};

type action =
  | Loaded(ConfessionData.confession)
  | UpdateInput(string)
  | Submit;

[@react.component]
let make = (~id) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Loaded(data) => {...state, input: "", confession: Some(data)}
        | UpdateInput(newInput) => {...state, input: newInput}
        | Submit => {...state, submitted: true}
        },
      {confession: None, input: "", submitted: false},
    );

  React.useEffect0(() => {
    ConfessionData.fetchConfessionWithComments(id, data =>
      dispatch(Loaded(data))
    )
    |> ignore;
    None;
  });

  <div>
    {switch (state.confession) {
     | Some(confession) =>
       <div>
         <ConfessionListItem key={confession.id} index=1 confession />
         <form
           className="StoryListItem_commentRow"
           onSubmit={event => {
             ReactEvent.Form.preventDefault(event);
             let _ = ConfessionData.createComment(confession.id, state.input);

             let newComment: ConfessionData.confessionComment = {
               message: state.input,
               id: state.input,
               ts: 123,
             };

             let newCommentArray = [|newComment|];

             let newComments: ConfessionData.comments = {
               commentsArray:
                 Array.concat(
                   confession.comments.commentsArray,
                   newCommentArray,
                 ),
             };

             let newData: ConfessionData.confession = {
               message: confession.message,
               id: confession.id,
               ts: confession.ts,
               comments: newComments,
             };

             dispatch(Loaded(newData));
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
       </div>
     | None => React.string("loading")
     }}
  </div>;
};
