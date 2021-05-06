open Belt;
open Utils;

type state = {
  recentConfessions: ConfessionData.recentConfessions,
  loading: bool,
};

type action =
  | Loaded(ConfessionData.recentConfessions)
  | Loading;

let initialState = {recentConfessions: [||], loading: true};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Loading => {...state, loading: true}
        | Loaded(data) =>
          let updatedRecentConfessions = Array.concat(state.recentConfessions, data);
          {recentConfessions: updatedRecentConfessions, loading: false};
        },
      initialState,
    );

  React.useEffect0(() => {
    ConfessionData.fetchConfessions(payload =>
    //Js.log(payload))
    dispatch(Loaded(payload))
    )
    |> ignore;
    None;
  });

  <div>
  {state.loading
    ? ReasonReact.string("Loading...")

    : 
    {state.recentConfessions->
              
               Array.mapWithIndex((index, confession)=>
               
                 <ConfessionListItem 
                 //key={string_of_int(int_of_string(confession.id) + index)}
                 key={confession.id}
                 index
                 confession
                 showCommentInput = false/>
                 )
           ->React.array;          
          }
  }
  </div>;
};
