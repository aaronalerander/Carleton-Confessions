open Belt;

type state = {
  recentConfessions: option(ConfessionData.recentConfessions),
  loading: bool,
};

type action =
  | Loaded(ConfessionData.recentConfessions)
  | Loading;

//let initialState = {recentConfessions: [||], loading: true};
let initialState = {recentConfessions: None, loading: true};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Loading => {...state, loading: true}
        | Loaded(data) => {recentConfessions: Some(data), loading: false}
        },
      initialState,
    );

  // React.useEffect0(() => {
  //   // ConfessionData.fetchConfessions(payload => dispatch(Loaded(payload)))
  //   // ConfessionData.fetchConfessions(payload => Js.log(payload))
  //   // ConfessionData.fetchConfessions(payload => Js.log(payload))
  //   ConfessionData.fetchConfessions(payload => {
  //     switch (payload) {
  //     | Some(data) => Js.log("this again")
  //     // | Some(ConfessionData.recentConfessions) => Js.log("this again")
  //     | None => Js.log("this")
  //     | Some(payload) => Js.log(payload)
  //     //dispatch(Loaded(payload))
  //     }
  //   })
  //   |> ignore;
  //   None;
  // });

  React.useEffect0(() => {
    ConfessionData.fetchConfessions(payload =>
      dispatch(Loaded(Some(payload)))
    )
    |> ignore;
    None;
  });

  <div>
    {state.loading
       ? ReasonReact.string("Loading...")
       : {
         state.recentConfessions
         ->Array.mapWithIndex((index, confession) =>
             <ConfessionListItem key={confession.id} index confession />
           )
         ->React.array;
       }}
  </div>;
};
