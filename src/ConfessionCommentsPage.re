open Belt;
open Utils;

type state = {
  confession: option(ConfessionData.confession),
  //confession: ConfessionData.confession,
  
};

type action =
  | Loaded(ConfessionData.confession);

//let initialState = {confession: None, loading: true};

[@react.component]
let make = (~id) => {

  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Loaded(data) => {confession: Some(data)};
        }, {confession : None});

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
    | Some(data) =>
      <div>
      <h1> {React.string(data.message)}</h1>
      <h1> {React.string(data.id)}</h1>
      <ConfessionListItem 
                 //key={string_of_int(int_of_string(confession.id) + index)}
                 key={data.id}
                 index=1
                 confession= data
                 showCommentInput = true/>

      
       // {renderTitle(story)}
       // {renderByline(story)}
       // <CommentList story />
       {React.string("info is here")}
      </div>
    | None => React.string("loading")
    }}
  </div>;
};
