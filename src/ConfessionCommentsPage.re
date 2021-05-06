open Belt;
open Utils;

type state = {
  confession: option(ConfessionData.confession),
  //confession: ConfessionData.confession,
  input: string,
  submitted: bool
  
};

type action =
  | Loaded(ConfessionData.confession)
  | UpdateInput(string)
  | Submit;

//let initialState = {confession: None, loading: true};

[@react.component]
let make = (~id) => {

  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Loaded(data) => {...state, input:"", confession: Some(data)};
        | UpdateInput(newInput) => {...state, input: newInput}
        | Submit => {...state, submitted: true}
        }, {confession : None, input:"", submitted:false});

  React.useEffect0(() => {
    ConfessionData.fetchConfessionWithComments(id,data =>
    //Js.log(data)
    dispatch(Loaded(data))
    )
    |> ignore;
    None;
  });

  <div>
//   {state.loading
//     ? ReasonReact.string("Loading...")
//     : state.recentConfessions->(
//                Array.mapWithIndex((index, confession)=>
//                  <ConfessionListItem 
//                  //key={string_of_int(int_of_string(confession.id) + index)}
//                  key={confession.id}
//                  index
//                  confession/>
//                  )
//              )
//            ->React.array;
//   }




{switch (state.confession) {
    | Some(confession) =>
      <div>
      <h1> {React.string(confession.message)}</h1>
      <h1> {React.string(confession.id)}</h1>
      <ConfessionListItem 
                 //key={string_of_int(int_of_string(confession.id) + index)}
                 key={confession.id}
                 index=1
                 confession= confession
                 showCommentInput = true/>

      
       // {renderTitle(story)}
       // {renderByline(story)}
       // <CommentList story />
       {React.string("info is here")}

       //<button>{React.string("click this button")}</button>

       <form  
       onSubmit={event => {
       ReactEvent.Form.preventDefault(event);


       let _ = ConfessionData.createComment(confession.id, state.input);  

       let newComment : ConfessionData.confessionComment = {
        message: state.input,
         id: state.input,
         ts:123
       }
       Js.log(confession.comments)
       Js.log(newComment)

       let newCommentArray = [|newComment|]

      let newComments : ConfessionData.comments ={
       commentsArray : Array.concat(confession.comments.commentsArray, newCommentArray)
      }

       let newData : ConfessionData.confession = {
         message: confession.message,
         id: confession.id,
         ts: confession.ts,
         comments: newComments
        }

        dispatch(Loaded(newData));


       //myfunc(state.input);
       //let value = state.input;
       Js.log("gonna submit " )
       //let _ = ConfessionData.createConfession(value);       
       }}>

       <label htmlFor="search"> {ReasonReact.string("Search")} </label>
                <textarea
                id="search"
                name="search "
                value={state.input}
                onChange={event => {
                    let value = ReactEvent.Form.target(event)##value;
                    dispatch(UpdateInput(value));

                }}
                />

       <button type_="submit">
       {ReasonReact.string("Submit Search")}
       </button>
   </form>










      </div>
    | None => React.string("loading")
    }}
  </div>;
};
